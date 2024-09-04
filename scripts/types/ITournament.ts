import { Tournament, TournamentConfig, TournamentPayload } from "./definitions";

export default interface ITournament {
    isAvailable(): boolean;
    isContextLBAvailable(): boolean;
    getLeaderboardAsync(leaderboardId: string): Promise<FBInstant.Leaderboard>;
    createTournamentAsync(initialScore: number, config: TournamentConfig, data: TournamentPayload): Promise<Tournament>;
    shareTournamentAsync(score: number, data: TournamentPayload): Promise<boolean>;
    joinTournamentAsync(tournamnetId: string): Promise<boolean>;
    postTournamentScoreAsync(score: number): Promise<boolean>;
    getTournamentsAsync(): Promise<Tournament[]>;
    getTournamentAsync(): Promise<Tournament>;
    isInTournamentContext(): boolean;
}