import { Tournament, TournamentConfig, TournamentPayload } from "./types/definitions";
import ITournament from "./types/ITournament";

export class TournamentAPI {
    private TAG = "TournamentPlatformChooser";

    static getInstance(): TournamentAPI {
        return this.instance;
    }

    static init(tournamentDelegate: ITournament) {
        if (!this.instance) {
            this.instance = new TournamentAPI(tournamentDelegate);
        }
    }
    constructor(tournamentDelegate: ITournament) {
        this.tournamentDelegate = tournamentDelegate;
    }
    getLeaderboardAsync(leaderboardId: string): Promise<FBInstant.Leaderboard> {
        return this.tournamentDelegate.getLeaderboardAsync(leaderboardId);
    }
    isAvailable(): boolean {
        return this.tournamentDelegate.isAvailable();
    }
    isContextLBAvailable(): boolean {
        return this.tournamentDelegate.isContextLBAvailable();
    }

    createTournamentAsync(initialScore: number, config: TournamentConfig, data: TournamentPayload): Promise<Tournament> {
        if (!this.isAvailable()) {
            return Promise.reject("NOT_AVAILABLE");
        }
        return this.tournamentDelegate.createTournamentAsync(initialScore, config, data);
    }

    shareTournamentAsync(score: number, data: TournamentPayload): Promise<boolean> {
        if (!this.isAvailable()) {
            return Promise.reject("NOT_AVAILABLE");
        }
        return this.tournamentDelegate.shareTournamentAsync(score, data)
    }

    joinTournamentAsync(tournamnetId: string): Promise<boolean> {
        if (!this.isAvailable()) {
            return Promise.reject("NOT_AVAILABLE");
        }
        return this.tournamentDelegate.joinTournamentAsync(tournamnetId);
    }

    postTournamentScoreAsync(score: number): Promise<boolean> {
        if (!this.isAvailable()) {
            return Promise.reject("NOT_AVAILABLE");
        }
        return this.tournamentDelegate.postTournamentScoreAsync(score);
    }

    getTournamentAsync(): Promise<Tournament> {
        if (!this.isAvailable()) {
            return Promise.reject("NOT_AVAILABLE");
        }
        return this.tournamentDelegate.getTournamentAsync();
    }
    getTournamentsAsync(): Promise<Tournament[]> {
        if (!this.isAvailable()) {
            return Promise.reject("NOT_AVAILABLE");
        }
        return this.tournamentDelegate.getTournamentsAsync();
    }

    isInTournamentContext(): boolean {
        return this.tournamentDelegate.isInTournamentContext();
    }

    private static instance: TournamentAPI;
    private tournamentDelegate: ITournament;
}