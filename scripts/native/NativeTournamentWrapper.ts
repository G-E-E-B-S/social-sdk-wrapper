import { Tournament, TournamentConfig, TournamentPayload } from "../types/definitions";
import { StringArgAPICallback } from "./types";

declare const social;
interface ITournamentListener {
    onTournamentsFetchError: (error: string) => void;
    onTournamentsFetchComplete: (tournamentsJson: string) => void;
    onTournamentFetchError: (error: string) => void;
    onTournamentFetchComplete: (tournamentStr: string) => void;
    onPostTournamentScorefailed: (error: string) => void;
    onPostTournamentScoreSuccess: (tournamentId: string) => void;
    onTournamentSharefailed: (error: string) => void;
    onTournamentShareSuccess: (tournamentId: string) => void;
    onTournamentCreatefailed: (error: string) => void;
    onTournamentCreateSuccess: (tournamentId: string) => void;
}
interface ITournamentDelegate {
    getTournaments(): void;
    getTournament(): void;
    postTournamentScore(score: number, tournamentId: string): void;
    shareTournament(score: number, tournamentId: string): void;
    createTournament(initialScore: number, title: string, endTime: number, scoreType: string, image: string, sortOrder: string, arg6: string): void;
}
export default class NativeTournamentWrapper {

    constructor() {
        this.setupDelegate();
    }

    createTournamentAsync(initialScore: number, config: TournamentConfig, data: TournamentPayload, onSuccess: StringArgAPICallback, onFailure: StringArgAPICallback) {
        this.onTournamentCreateSuccess = onSuccess;
        this.onTournamentCreatefailed = onFailure;

        const title = config.title ? config.title : "";
        const endTime = config.endTime ? config.endTime : 0;
        const scoreType = config.scoreFormat ? config.scoreFormat : "";
        const image = config.image ? config.image : "";
        const sortOrder = config.sortOrder ? config.sortOrder : "";
        this.tournamentDelegate.createTournament(initialScore, title, endTime, scoreType, image, sortOrder, JSON.stringify(data));
    }

    shareTournamentAsync(score: number, tournamentId: string, onSuccess: StringArgAPICallback, onFailure: StringArgAPICallback) {
        this.onTournamentShareSuccess = onSuccess;
        this.onTournamentSharefailed = onFailure;
        this.tournamentDelegate.shareTournament(score, tournamentId);
    }

    postTournamentScoreAsync(score: number, tournamentId: string, onSuccess: StringArgAPICallback, onFailure: StringArgAPICallback) {
        this.onPostTournamentScoreSuccess = onSuccess;
        this.onPostTournamentScorefailed = onFailure;
        this.tournamentDelegate.postTournamentScore(score, tournamentId);
    }
    getTournamentAsync(callback: (tournament: Tournament) => void, onFailure: StringArgAPICallback) {
        this.onTournamentFetchComplete = callback;
        this.onTournamentFetchError = onFailure;
        this.tournamentDelegate.getTournament();
    }

    getTournamentsAsync(onSuccess: (tournaments: Tournament[]) => void, onFailure: StringArgAPICallback) {
        this.onTournamentsFetchComplete = onSuccess;
        this.onTournamentsFetchError = onFailure;
        this.tournamentDelegate.getTournaments();
    }

    private setupDelegate() {
        this.tournamentDelegate = social.getTournamentController();
        const obj = {} as ITournamentListener;
        obj.onTournamentCreateSuccess = (tournamentId: string) => {
            this.onTournamentCreateSuccess(tournamentId);
        };
        obj.onTournamentCreatefailed = (error: string) => {
            this.onTournamentCreatefailed(error);
        };
        obj.onTournamentShareSuccess = (tournamentId: string) => {
            this.onTournamentShareSuccess(tournamentId);
        };
        obj.onTournamentSharefailed = (error: string) => {
            this.onTournamentSharefailed(error);
        };
        obj.onPostTournamentScoreSuccess = (tournamentId: string) => {
            this.onPostTournamentScoreSuccess(tournamentId);
        };
        obj.onPostTournamentScorefailed = (error: string) => {
            this.onPostTournamentScorefailed(error);
        };
        obj.onTournamentFetchComplete = (tournamentStr: string) => {
            try {
                this.onTournamentFetchComplete(JSON.parse(tournamentStr));
            } catch (e) {
                this.onTournamentFetchError(null);
            }
        };
        obj.onTournamentFetchError = (error: string) => {
            this.onTournamentFetchError(error);
        }
        obj.onTournamentsFetchComplete = (tournamentsJson: string) => {
            try {
                const tournaments = JSON.parse(tournamentsJson) as Tournament[];
                this.onTournamentsFetchComplete(tournaments);
            } catch (error) {
                console.error("Error parsing json %s", JSON.stringify(error));
                this.onTournamentsFetchComplete([]);
            }
        }
        obj.onTournamentsFetchError = (error: string) => {
            this.onTournamentsFetchError(error);
        }
        social.setTournamentListener(obj);
    }

    private onTournamentCreateSuccess: StringArgAPICallback;
    private onTournamentCreatefailed: StringArgAPICallback;
    private onTournamentShareSuccess: StringArgAPICallback;
    private onTournamentSharefailed: StringArgAPICallback;
    private onPostTournamentScoreSuccess: StringArgAPICallback;
    private onPostTournamentScorefailed: StringArgAPICallback;
    private onTournamentFetchComplete: (tournaments: Tournament) => void;
    private onTournamentFetchError: StringArgAPICallback;
    private onTournamentsFetchComplete: (tournaments: Tournament[]) => void;
    private onTournamentsFetchError: StringArgAPICallback;
    private tournamentDelegate: ITournamentDelegate;
}