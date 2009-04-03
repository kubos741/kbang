
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


class BadGameStateException
{
public:
    BadGameStateException() {}
};

class BadGameException {};

class TooManyCardsInHandException {};

class BadCardException {};





#endif // GAMEEXCEPTIONS_H
