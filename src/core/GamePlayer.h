/*
 * GamePlayer.h
 *
 *
 * The GamePlayer class is an adapter between the GameEngine and the
 * Abstract Player class. It simplifies the interface for an AbstractPlayer
 * but provides the GameEngine with the functions it needs to do its job
 * more simply.
 *
 * The GamePlayer provides a full model for interactions that you may see
 * performed on a Player in the domain model sense, with AbstractPlayer being
 * used to simplify communications with the actual players over different mechanisms.
 *
 * This class handles the communications between the GameEngine and the AbstractPlayers
 * subclasses and provides other functions that don't need to be exposed to the AbstractPlayer.
 */

#ifndef GAMEPLAYER_H_
#define GAMEPLAYER_H_

#include <string>
#include <iostream>
#include <assert.h>

#include "Hand.h"
#include "Card.h"
#include "Money.h"
#include "AbstractPlayer.h"

namespace GameEngineCore {

class GamePlayer {

	public:
		explicit GamePlayer(AbstractPlayer& player_impl);
		GamePlayer(const GamePlayer& gp);
		GamePlayer operator=(const GamePlayer& gp);

		const Hand* const GetHand() const { return &m_hand; }

		void SetPot(Money new_value);
		const Money& GetPot() const { return m_pot; }

		void DealerAnnounce(std::string dealer);
		void SmallBlindAnnounce(std::string payer, Money amount);
		void BigBlindAnnounce(std::string payer, Money amount);
		void OpponentMoneyUpdate(std::string player, Money pot, Money bank);
		void OpponentCardAnnounce(std::string player, const Hand& players_hand);
		void WinnerAnnounce(std::string player, Money winnings);

		bool IsPlaying() const;
		std::string GetName() const;
		Money GetTotalBalance() const;
		void SetTotalBalance(Money new_value);
		void CardDealt(const Card& new_card);
		bool IsAllIn();
		void Fold();

		Money PayPot(Money value); //moves money from bank to pot
		GameChoice MakeChoice(Money minimum_bid);

		std::string ToString() const;

	private:
		AbstractPlayer *m_player_impl; //GamePlayer does not own pointer.
		Hand m_hand;
		Money m_pot;
		bool m_folded;

};

std::ostream& operator<<(std::ostream& os, const GamePlayer& ply);

}

#endif /* GAMEPLAYER_H_ */
