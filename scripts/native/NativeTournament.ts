import ITournamentDelegate from "../types/ITournament";
import { Tournament, TournamentConfig, TournamentPayload } from "../types/definitions";
import NativeTournamentWrapper from "./NativeTournamentWrapper";

export interface IAvailabilityChecker {
    isAvailable(): boolean;
}

class NativeTournamentObj implements Tournament {
    constructor(id: string, endTime? : number, payload? : unknown) {
        this.id = id;
        this.endTime = endTime;
        this.payload = payload;
    }
    getID(): string {
        return this.id;
    }
    getContextID(): string {
        return this.id;
    }
    getEndTime(): number {
        return this.endTime;
    }
    getPayload() {
        return this.payload;
    }
    private id: string;
    private endTime: number;
    private payload: unknown;
}

export default class NativeTournament implements ITournamentDelegate {
/**
     * 
     * @param availabilityChecker helper to check if api is available in this session
     */
    constructor(availabilityChecker: IAvailabilityChecker) {
        this.availabilityChecker = availabilityChecker;
        this.tournamentWrapper = new NativeTournamentWrapper();
    }
    getLeaderboardAsync(): Promise<FBInstant.Leaderboard> {
        return Promise.reject("API_NOT_SUPPORTED")
    }
    isAvailable(): boolean {
      return this.availabilityChecker.isAvailable();
    }
    isContextLBAvailable(): boolean {
        return false;
    }
    getTournamentAsync(): Promise<Tournament> {
        if (!this.availabilityChecker.isAvailable()) {
            return Promise.reject("API_NOT_AVAILABLE");
        }
        if (this.currentTournament) {
            return Promise.resolve(this.currentTournament);
        }
        return new Promise((resolve, reject) => {
            try {
                this.tournamentWrapper.getTournamentAsync((tournament: Tournament) => {
                    if (tournament) {
                        this.currentTournament = tournament;
                        this.currentTournamentId = tournament.getID();
                        return resolve(tournament);
                    } else {
                        reject("INVALID_DATA");
                    }
                }, (error: string) => {
                    return reject(error);
                });
            } catch (e) {
                return reject(e);
            }
        });
    }
    createTournamentAsync(initialScore: number,config: TournamentConfig, data: TournamentPayload): Promise<Tournament>  {
        if (!this.availabilityChecker.isAvailable()) {
            return Promise.reject("API_NOT_AVAILABLE");
        }
        return new Promise((resolve, reject) => {
            try {
                this.tournamentWrapper.createTournamentAsync(initialScore, config, data, (tournamentId: string) => {
                    this.currentTournamentId = tournamentId;
                    this.currentTournament = new NativeTournamentObj(tournamentId, config.endTime, data);
                    return resolve(this.currentTournament);
                }, (error: string) => {
                    return reject(error);
                });
            } catch (e) {
                return reject(e);
            }
        });
    }

    shareTournamentAsync(score: number, data: TournamentPayload): Promise<boolean> {
        // TODO: add data payload.
        if (!this.availabilityChecker.isAvailable()) {
            return Promise.resolve(false);
        }
        const promise = new Promise<boolean>((resolve, reject) => {
            try {
                this.tournamentWrapper.shareTournamentAsync(score, this.currentTournamentId, () => {
                    resolve(true);
                }, (error: string) => {
                    return reject(error);
                });
            } catch (e) {
                reject(e);
            }
        });
        return promise;
    }

    joinTournamentAsync(): Promise<boolean> {
        if (!this.availabilityChecker.isAvailable()) {
            return Promise.resolve(false);
        }
        return Promise.reject("UNSUPPORTED_OPERATION");
    }

    postTournamentScoreAsync(score: number): Promise<boolean> {
        if (!this.availabilityChecker.isAvailable()) {
            return Promise.resolve(false);
        }
        const promise = new Promise<boolean>((resolve, reject) => {
            try {
                return this.tournamentWrapper.postTournamentScoreAsync(score, this.currentTournamentId, () => {
                    resolve(true);
                }, (error: string) => {
                    return reject(error);
                });
            } catch (error) {
                return reject(error);
            }
        });
        return promise;
    }

    getTournamentsAsync(): Promise<Tournament[]> {
        if (!this.availabilityChecker.isAvailable()) {
            return Promise.resolve([]);
        }
        return new Promise((resolve, reject) => {
            try {
                this.tournamentWrapper.getTournamentsAsync((tournaments: Tournament[]) => {
                    return resolve(tournaments);
                }, (error: string) => {
                    return reject(error);
                });
            } catch (error) {
                return reject(error);
            }
        });
    }

    isInTournamentContext(): boolean {
        if (this.currentTournamentId) {
            return true;
        } else {
            return false;
        }
    }
    private availabilityChecker: IAvailabilityChecker;
    private currentTournamentId: string = null;
    private currentTournament: Tournament = null;
    private tournamentWrapper: NativeTournamentWrapper = null;
}