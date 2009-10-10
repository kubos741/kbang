#ifndef SIMPLETYPEPARSER_H
#define SIMPLETYPEPARSER_H

#include "gametypes.h"
#include <QDateTime>
#include <QList>
#include <QLocale>

////////////////////////////////////////////////////////////////////////////////
//    QString conversions
////////////////////////////////////////////////////////////////////////////////
#include <QStringList>

inline QString toString(const QString& s)
{
    return s;
}

inline void fromString(const QString& s, QString& t)
{
    t = s.toInt();
}

////////////////////////////////////////////////////////////////////////////////
//    Integer conversions
////////////////////////////////////////////////////////////////////////////////


inline QString toString(const bool& b)
{
    return (b ? "true" : "false");
}

inline void fromString(const QString& s, bool& b)
{
    b = (s.toLower() == "true");
}

inline QString toString(const qint8& i)
{
    return QString::number(i);
}

inline void fromString(const QString& s, qint8& i)
{
    i = (qint8)s.toShort();
}

inline QString toString(const quint8& i)
{
    return QString::number(i);
}

inline void fromString(const QString& s, quint8& i)
{
    i = (quint8)s.toUShort();
}

inline QString toString(const qint16& i)
{
    return QString::number(i);
}

inline void fromString(const QString& s, qint16& i)
{
    i = s.toShort();
}

inline QString toString(const quint16& i)
{
    return QString::number(i);
}

inline void fromString(const QString& s, quint16& i)
{
    i = s.toUShort();
}

inline QString toString(const int& i)
{
    return QString::number(i);
}

inline void fromString(const QString& s, int& i)
{
    i = s.toInt();
}

inline QString toString(const uint& i)
{
    return QString::number(i);
}

inline void fromString(const QString& s, uint& i)
{
    i = s.toUInt();
}

inline QString toString(const long& i)
{
    return QString::number(i);
}

inline void fromString(const QString& s, long& i)
{
    i = s.toLong();
}

inline QString toString(const ulong& i)
{
    return QString::number(i);
}

inline void fromString(const QString& s, ulong& i)
{
    i = s.toULong();
}

inline QString toString(const qlonglong& i)
{
    return QString::number(i);
}

inline void fromString(const QString& s, qlonglong& i)
{
    i = s.toLongLong();
}

inline QString toString(const qulonglong& i)
{
    return QString::number(i);
}

inline void fromString(const QString& s, qulonglong& i)
{
    i = s.toULongLong();
}

////////////////////////////////////////////////////////////////////////////////
//    Enum conversions
////////////////////////////////////////////////////////////////////////////////

inline QString toString(const PlayerRole& r) {
    return playerRoleToString(r);
}

inline void fromString(const QString& s, PlayerRole& r) {
    r = stringToPlayerRole(s);
}

inline QString toString(const ClientType& r) {
    return clientTypeToString(r);
}

inline void fromString(const QString& s, ClientType& r) {
    r = stringToClientType(s);
}

inline QString toString(const PocketType& r) {
    return pocketTypeToString(r);
}

inline void fromString(const QString& s, PocketType& r) {
    r = stringToPocketType(s);
}

inline QString toString(const CardType& r) {
    return cardTypeToString(r);
}

inline void fromString(const QString& s, CardType& r) {
    r = stringToCardType(s);
}

inline QString toString(const ReactionType& r) {
    return reactionTypeToString(r);
}

inline void fromString(const QString& s, ReactionType& r) {
    r = stringToReactionType(s);
}

inline QString toString(const GameParticipantType& r) {
    return gameParticipantTypeToString(r);
}

inline void fromString(const QString& s, GameParticipantType& r) {
    r = stringToGameParticipantType(s);
}

inline QString toString(const CardSuit& r) {
    return cardSuitToString(r);
}

inline void fromString(const QString& s, CardSuit& r) {
    r = stringToCardSuit(s);
}

inline QString toString(const CardRank& r) {
    return cardRankToString(r);
}

inline void fromString(const QString& s, CardRank& r) {
    r = stringToCardRank(s);
}

inline QString toString(const GameState& r) {
    return gameStateToString(r);
}

inline void fromString(const QString& s, GameState& r) {
    r = stringToGameState(s);
}

inline QString toString(const GamePlayState& r) {
    return gamePlayStateToString(r);
}

inline void fromString(const QString& s, GamePlayState& r) {
    r = stringToGamePlayState(s);
}

////////////////////////////////////////////////////////////////////////////////
//    Qt Conversions
////////////////////////////////////////////////////////////////////////////////

inline QString toString(const QDateTime& r) {
    return r.toString(Qt::ISODate);
}

inline void fromString(const QString& s, QDateTime& r) {
    r = QDateTime::fromString(s, Qt::ISODate);
}

inline QString toString(const QList<QLocale>& r) {
    QStringList res;
    foreach (const QLocale& l, r) {
        res.append(l.name());
    }
    return res.join(",");
}

inline void fromString(const QString& s, QList<QLocale>& r) {
    r.clear();
    foreach (const QString& l, s.split(",")) {
        r.append(QLocale(l));
    }
}

#endif // SIMPLETYPEPARSER_H