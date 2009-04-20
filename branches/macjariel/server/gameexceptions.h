
#ifndef GAMEEXCEPTIONS_H
#define GAMEEXCEPTIONS_H


class BadPlayerException
{
public:
    BadPlayerException(int playerId): m_playerId(playerId) {}
    int playerId() const { return m_playerId; }
private:
    int m_playerId;
};


class BadGameStateException {};

class OneBangPerTurnException: public BadGameStateException {};
class TwoSameOnTableException: public BadGameStateException {};


class BadTargetPlayerException: public BadGameStateException {};
class PlayerOutOfRangeException: public BadTargetPlayerException {};


class BadGameException {};

class TooManyCardsInHandException {};

class BadCardException {};

class BadUsageException {};



#endif // GAMEEXCEPTIONS_H
