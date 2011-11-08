#include <QtCore/QCoreApplication>
#include <QStringList>
#include <QString>
#include <QVector>
#include <iostream>
#include <stdio.h>
const QString EMPTY_CHAR = "_";
int main(int argc, char *argv[])
{
  QVector<QStringList> states;
  QStringList FENS;
  /*
    FENS.append("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    FENS.append("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    FENS.append("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2");
    FENS.append("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");
  */

  FENS.append("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");

  FENS.append("rnbqkbnr/ppp1pppp/8/3p4/3P4/4P3/PPP2PPP/RNBQKBNR b KQkq - 0 2");

  FENS.append("rnbqkb1r/ppp1pppp/5n2/3p4/3P4/4P3/PPP2PPP/RNBQKBNR w KQkq - 1 2");

  /*
    rnbqkbnr
    pp1ppppp
    8
    2p5
    2P3
    5N2
    PPPP1PPP
    RNBQKB1R b KQkq - 1 2

  */
  foreach(QString FEN, FENS)
    {
      std::cout << "Processing FEN " << qPrintable(FEN) << std::endl;
      QStringList ranks = FEN.split(QRegExp("[/\\s]"));
      QStringList ExpandedRanks;
      //  foreach(QString s, ranks)
      //      std::cout << qPrintable(s) << std::endl;

      // Expand empties
      // Find first number to expand
      foreach(QString r, ranks)
        {
          int npos = r.indexOf(QRegExp("[\\d]"));
          if(npos != -1)
            {

              do
                {
                  //std::cout << " Found field to expand at " << npos << std::endl;
                  // Get expansion lenght
                  int len = r.at(npos).digitValue();
                  // Remove digit and insert expansion
                  //std::cout << "Inserting ... " << qPrintable(EMPTY_CHAR.repeated(len)) << " at " << npos << std::endl;
                  r = r.remove(npos, 1).insert(npos, EMPTY_CHAR.repeated(len));
                  npos = r.indexOf(QRegExp("[\\d]"));
                } while(npos != -1);
              ExpandedRanks.append(r);

            }
          else
            {
              // std::cout << "Nothing to expand at rank " << qPrintable(r) << std::endl;
              ExpandedRanks.append(r);
            }
        }

      foreach(QString s, ExpandedRanks)
        std::cout << qPrintable(s) << std::endl;
      states.append(ExpandedRanks);
    }


  // Compare state vectors
  /*for(QVector<QStringList>::const_iterator iter = states.constBegin(); begin != states.constEnd(); ++iter)
    {
    QStringList curr = iter;
    QStringList next = iter+1;

    }
  */
  std::cout << "Calculating Algebraic Notation" << std::endl;
  QVectorIterator<QStringList> i(states);
  QStringList moves;
  while(i.hasNext())
    {
      QStringList curr = i.next();

      if(i.hasNext())
        {

          // We have both states
          QStringList next = i.peekNext();
          if(curr.length() != next.length() )
            qFatal("State Corruption!");

          // Compare Ranks
          for(int r = 0; r < 8; r++)
            {
              QString rank1 = curr.at(r);
              QString rank2 = next.at(r);

              // Check for differences
              for(int c = 0; c < rank1.length(); c++)
                {

                  char piece1 = rank1.at(c).toLatin1();
                  char piece2 = rank2.at(c).toLatin1();
                  if(piece1 != piece2)
                    {
                      // Possible change!
                      char col = (char)(c+'A');
                      int rankn = 8-r;
                      std::cout << "Piece: " << piece1 << " , " << piece2 << " @ " << col  << "." << rankn << std::endl;
                      // Only save valid pieces

                      if(QChar(piece1)==EMPTY_CHAR.at(0))
                        {
                          if(piece2 == 'P' || piece2 == 'p')
                            piece2 =' ';
                          moves.append(QString(piece2 + QString(col)+QChar::fromAscii(rankn+'0')));
                        }
                    }
                }


            }



        }
      else
        std::cout << "Reached end of states" << std::endl;

    }

  // Cleaup Pieces
  foreach(QString s, moves)
    std::cout << s.toLatin1().constData() << std::endl;

  getchar();
}
