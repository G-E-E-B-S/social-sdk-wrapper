import Foundation
import FBSDKGamingServicesKit
import UIKit
@objc public class TournamentParams: NSObject {
    @objc public var title: String?;
    @objc public var endTime: Date?;
    @objc public var scoreType: String?;
    @objc public var sortOrder: String?;
    @objc public var image: UIImage?;
    @objc public var paylod: String?;
}
@objc public class TournamentDelegate : NSObject, ShareTournamentDialogDelegate {
    @objc public func createTournament(tournamentParams: TournamentParams) {
        let scoreType = TournamentScoreType(rawValue: tournamentParams.scoreType ?? "numeric");
        let sortOrder = TournamentSortOrder(rawValue: tournamentParams.sortOrder ?? "higherIsBetter");
        let tournamentConfig = TournamentConfig(title: tournamentParams.title, endTime: tournamentParams.endTime, scoreType: scoreType, sortOrder: sortOrder, image: tournamentParams.image, payload: tournamentParams.paylod);
        let shareDialog = ShareTournamentDialog(delegate: self);
        do {
            try shareDialog.show(initialScore: 0, config: tournamentConfig);
        } catch {
            // TODO: send feedback to caller
            print("shareTournament:createTournament Caught error: \(error)");
        }
    }
    @objc public func shareTournament(initialScore: Int, tournamentId: String) {
        let shareDialog = ShareTournamentDialog(delegate: self);
        do {
            try shareDialog.show(score: initialScore, tournamentID: tournamentId);
        } catch {
            // TODO: send feedback to caller
            print("TournamentDelegate:shareTournament Caught error: \(error)");
        }
    }
    @objc public func postTournamentScore(score: Int, tournamentId: String) {
        TournamentUpdater().update(tournamentID: tournamentId, score: score) { result in
            switch result {
            case .success:
                // TODO: handle success
                break;
            case .failure(let error):
                print("TournamentDelegate:postTournamentScore got error: \(error)");
                // TODO: handle failure
                break;
            }
        }
    }
    @objc public func  fetchTournaments() {
        TournamentFetcher().fetchTournaments { result in
            switch result {
            case .success(let tournaments):
                // TODO: handle success
                print("fetchTournaments got tournaments: \(tournaments.count)");
                break;
            case .failure(let error):
                print("TournamentDelegate:fetchTournaments got error: \(error)");
                // TODO: handle failure
                break;
            }
        }
    }
    public func didComplete(dialog: ShareTournamentDialog, tournament: Tournament) {
        print("TournamentDelegate:didComplete: \(tournament.identifier)");
        onTournamentCreateSuccess(tournament.identifier);
    }
    
    public func didFail(withError error: Error, dialog: ShareTournamentDialog) {
        print("TournamentDelegate:didFail with error: \(error)");
    }
    
    public func didCancel(dialog: ShareTournamentDialog) {
        print("TournamentDelegate:didCancel");
    }
}
