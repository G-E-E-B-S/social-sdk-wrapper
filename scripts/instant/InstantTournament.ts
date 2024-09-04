import { Tournament, TournamentConfig, TournamentPayload } from "../types/definitions";
import ITournamentDelegate from "../types/ITournament";
import { InstantSafeTournament } from "./InstantSafeTournament";

export class InstantTournament implements ITournamentDelegate{
    getLeaderboardAsync(leaderboardId: string): Promise<FBInstant.Leaderboard> {
        try {
            return FBInstant.getLeaderboardAsync(leaderboardId)
                .then((leaderboard) => {
                    return leaderboard;
                }).catch((error) => {
                    return Promise.reject(error);
                });
        } catch (e) {
            return Promise.reject(e);
        }
    }
    getTournamentAsync(): Promise<Tournament> {
        return InstantSafeTournament.getTournamentAsync().then(tournament => {
            if (tournament) {
                return tournament;
            }
            return Promise.reject("API_NOT_SUPPORTED");
        });
    }
    isAvailable(): boolean {
        return typeof FBInstant !== 'undefined' && typeof FBInstant.tournament !== 'undefined';
    }
    isContextLBAvailable(): boolean {
        return true;
    }
    createTournamentAsync(initialScore: number, config: TournamentConfig, data: TournamentPayload): Promise<Tournament> {
        if (this.isInTournamentContext()) {
            return Promise.reject("ALREADY_IN_TOURNAMENT");
        }
        return InstantSafeTournament.createTournament(initialScore, config, data);
    }

    shareTournamentAsync(score: number, data: TournamentPayload): Promise<boolean> {
        return InstantSafeTournament.shareTournament(score, data);
    }

    joinTournamentAsync(tournamnetId: string): Promise<boolean> {
        return InstantSafeTournament.joinTournament(tournamnetId);
    }

    postTournamentScoreAsync(score: number): Promise<boolean> {
        return InstantSafeTournament.postScore(score);
    }

    getTournamentsAsync(): Promise<Tournament[]> {
        return InstantSafeTournament.getTournamentsAsync();
    }
    isInTournamentContext(): boolean {
        return InstantSafeTournament.isInTournamentContext();
    }
}
