import { Tournament, TournamentConfig, TournamentPayload } from "../types/definitions";

export class InstantSafeTournament {
    static createTournament(initialScore: number, config: TournamentConfig, data?: TournamentPayload): Promise<Tournament> {
        if (!this.isAvailable("tournament.createAsync")) {
            return Promise.reject("API_NOT_AVAILABLE");
        }
        try {
            return FBInstant.tournament.createAsync({ initialScore, config, data })
                .then((tournament) => {
                    // TODO: add analytics
                    // AnalyticsHelper.setUserProperty({"is_tournament": 1});
                    // AnalyticsHelper.setUserProperty({"tournament_id": tournament.getID()});
                    // FBInstantSafe.logFbAPIEvent("createTournamentAsync", true);
                    this.currentTournament = tournament;
                    return Promise.resolve(tournament);
                }).catch((error) => {
                    // FBInstantSafe.logFbAPIEvent("createTournamentAsync", false, error);
                    return Promise.reject(error);
                }) as Promise<Tournament>;
        } catch (e) {
            // FBInstantSafe.logFbAPIEvent("createTournamentAsync", false, e);
            console.log("createTournament API : %s", JSON.stringify(e));
            return Promise.reject(e);
        }
    }

    static shareTournament(score: number, data: TournamentPayload): Promise<boolean> {
        if (!this.isAvailable("tournament.shareAsync")) {
            return Promise.reject("API_NOT_AVAILABLE");
        }
        try {
            return FBInstant.tournament.shareAsync({score, data}).then(() => {
                return true;
            }).catch((reason) => {
                console.error("InstantSafeTournament::shareTournament %s", reason);
                return false;
            });
        } catch (e) {
            console.log("shareTournament API : %s", JSON.stringify(e));
            return Promise.reject(e)
        }
    }

    static joinTournament(tournamentId: string): Promise<boolean> {
        if (!this.isAvailable("tournament.joinAsync")) {
            return Promise.reject("API_NOT_AVAILABLE");
        }
        try {
            return FBInstant.tournament.joinAsync(tournamentId).then(() => {
                // get current tournament after joining.
                this.getTournamentAsync();
                return true;
            }).catch((reason) => {
                // TODO: track and console log
                return Promise.reject(reason);
            })
        } catch (e) {
            console.log("joinTournamentAsync API : %s", JSON.stringify(e));
            return Promise.reject(e);
        }
    }

    static postScore(score: number): Promise<boolean> {
        if (!this.isAvailable("tournament.postScoreAsync")) {
            return Promise.resolve(false);
        }
        try {
            return FBInstant.tournament.postScoreAsync(score).then(() => {
                return true;
            }).catch((reason) => {
                console.error("InstantSafeTournament::postScore %s", reason);
                return false;
            });
        } catch (e) {
            // FBInstantSafe.logFbAPIEvent("createTournamentAsync", false, e);
            console.log("postScoreSilently API : %s", JSON.stringify(e));
            return Promise.reject(e);
        }
    }

    static getTournamentsAsync(): Promise<Tournament[]> {
        if (!this.isAvailable("tournament.getTournamentsAsync")) {
            return Promise.resolve([]);
        }
        try {
            return FBInstant.tournament.getTournamentsAsync().then((tournaments: Tournament[]) => {
                return tournaments;
            }).catch((reason) => {
                console.error("InstantSafeTournament::getTournamentsAsync %s", reason);
                return [];
            });
        } catch (e) {
            // FBInstantSafe.logFbAPIEvent("createTournamentAsync", false, e);
            console.log("createTournament API : %s", JSON.stringify(e));
            return Promise.reject("fetchAllTournaments Api error:" + e);
        }
    }
    static getTournamentAsync(): Promise<Tournament> {
        if (!(typeof FBInstant != 'undefined' && FBInstant.getTournamentAsync)) {
            return Promise.reject("API_NOT_AVAILABLE");
        }
        if (this.currentTournament) {
            return Promise.resolve(this.currentTournament);
        }
        try {
            return FBInstant.getTournamentAsync().then((tournament: Tournament) => {
                this.currentTournament = tournament;
                return tournament;
            });
        } catch (e) {
            // FBInstantSafe.logFbAPIEvent("createTournamentAsync", false, e);
            console.log("createTournament API : %s", JSON.stringify(e));
            return Promise.reject("fetchAllTournaments Api error:" + e);
        }
    }
    static isInTournamentContext(): boolean {
        if (this.currentTournament) {
            return true;
        }
        return false;
    }
    private static isAvailable(apiName: string) {
        return typeof FBInstant != 'undefined' && this.isAPISupported(apiName);
    }

    private static isAPISupported(apiName: string): boolean {
        if (!this.supportedAPIs) {
            this.supportedAPIs = FBInstant.getSupportedAPIs();
        }
        return this.supportedAPIs.indexOf(apiName) > -1;
    }

    private static currentTournament: Tournament = null;
    private static supportedAPIs: Array<string>;
}
