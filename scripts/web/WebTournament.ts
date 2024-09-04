import { Tournament } from "../types/definitions";
import ITournament from "../types/ITournament";

export class WebTournament implements ITournament {
    getLeaderboardAsync(): Promise<FBInstant.Leaderboard> {
        return Promise.reject("API_NOT_SUPPORTED")
    }
    isAvailable(): boolean {
        return false;
    }
    isContextLBAvailable(): boolean {
        return false;
    }
    createTournamentAsync(): Promise<Tournament> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    shareTournamentAsync(): Promise<boolean> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    joinTournamentAsync(): Promise<boolean> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    postTournamentScoreAsync(): Promise<boolean> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    getTournamentsAsync(): Promise<Tournament[]> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    getTournamentAsync(): Promise<Tournament> {
        return Promise.reject("API_NOT_SUPPORTED");
    }
    isInTournamentContext(): boolean {
        return false;
    }
}