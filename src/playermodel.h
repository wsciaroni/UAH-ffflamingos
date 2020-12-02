#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QString>
#include <QTcpSocket>
#include <QTimer>

/**
 * Position Enumeration
 * Used to determine which spot the player will be displayed in and able to
 * control
 */
enum class PlayerPosition {
  NONE = 0,
  LOWER_LEFT = 1,
  UPPER_LEFT = 2,
  CENTER = 3,
  UPPER_RIGHT = 4,
  LOWER_RIGHT = 5,
};

/**
 * Dynamically allocate one of these players for each player
 */
class PlayerModel : public QObject {
  Q_OBJECT

 private:
  // Id
  /// Unique User id used to allow name changes in the future
  int uid = -1;

  /**
   * Set the User id
   * @param uid the int id of the user
   */
  void setUID(int uid);

  /// User Name
  QString userName = "";

  // Network
  /// Used to store the TCP Socket associated with the player
  QTcpSocket* tcpsockt = nullptr;

  // Gameplay
  /// Holds current score for player
  int score = 0;

  /// Determines which of the 5 flamingos the player will be.
  PlayerPosition positionID = PlayerPosition::NONE;

  // Gameplay - Cool Down Calc

  /**
   * Timer to reset ever 5 seconds
   * Should reset itself ever certain period of time.
   * This will prevent users from spamming space more than X times in 5 seconds
   */
  QTimer coolDownTimer;

  /// The number of times the space bar has been pressed since the cooldown
  /// timer has reset
  int numPressesSinceTimeReset = 0;

  /**
   * Timer to reset one period after each space bar press
   * Used as a single shot each time the space is pressed
   * Used to prevent user from pressing space faster than the animation can
   * complete
   */
  QTimer animationTimer;

  /// True when the player is not allowed to press space
  bool animationLocked = false;

  /** True when the timers are enabled
   * @todo these will need to be enabled at the start of gameplay. No need to
   * run timers in the menus
   */
  bool timersEnabled;

  /// The number of spaces allowed per each cooldown period
  const int numAllowedInTime = 4;

  /// The length of the time (in milliseconds) of the cooldown Period
  const int cooldownPeriod = 10000;

  /// The length of the time (in milliseconds) of the animation Period
  const int animationPeriod = 750;

  /**
   * Check to see if the player is allowed to lunge for food
   * @details returns true if BOTH (and)
   * - numPressesSinceTimeReset <= 5
   * - !animationLocked
   * @return True if the player is allowed to lunge for food (Timers aren't
   * blocking)
   */
  bool allowedToLunge();

 public:
  // Constructors / Destructors

  /**
   * Constructor to instanciate a player
   * @param uid Unique User ID
   * @param socket tcpsocket to communicate with player's machine
   */
  PlayerModel(int uid, QTcpSocket* socket);

  /**
   * Constructor to instanciate a player without a Socket
   * @param uid Unique User ID
   */
  PlayerModel(int uid);

  /**
   * Destructor
   */
  ~PlayerModel();

  // Id
  /**
   * Get the UserID
   * @return int userid
   */
  int getUID();

  /**
   * Sets the Player's name
   * @param name The new name for the user
   */
  void setName(QString name);

  /**
   * Get the user's Name
   * @return QString of the User's name
   */
  QString getName();

  // Network
  /**
   * Set Network connection.  Used to initialize a player
   * @param socket Recieves a pointer to a QTcpSocket for that player
   */
  void setTCPSocket(QTcpSocket* socket);

  /**
   * Get Network Connection
   * @return A pointer to type QTcpSocket is returned
   */
  QTcpSocket* getTCPSocket();

  // Gameplay
  /**
   * Set the score of the player
   * @warning This will overwrite the current score of this player completely
   * @param score The new value for the player's score
   */
  void setScore(int score);

  /**
   * Adds value to score.
   * @note Use this with a negative argument to decrement the score.
   * @param delta This value is added to the score.
   */
  void increaseScore(int delta);

  /**
   * Get the score of the player
   * @return the score as an int of the player
   */
  int getScore();

  /**
   * Sets the position of the player to a specified position
   * @param position Position ID
   */
  void setPositionId(PlayerPosition position);

  /**
   * Get the player's position
   * @return the players position id
   */
  PlayerPosition getPositionId();

  // Gameplay - Timers
  /**
   * Turn on the cool down functionality for player
   * - Start coolDownTimer
   * - set timersEnabled = true
   */
  void enableTimers();

  /**
   * Turn off the cool down functionality for player
   * @details will do the following
   * - stop both timers
   * - set timersEnabled = false
   */
  void disableTimers();

  /**
   * Used to take advantage of cool-down functionality
   *
   * @details will increment the appropriate areas to keep track of cool down
   *and animation timers
   * - Increment numPressesSinceTimeReset
   * - Check if allowedTolunge()
   * - Start the Animation timer
   * @return true if the player is allowed to lunge and successfully lunges else
   *false
   */
  bool spacePressed();

  /**
   * Used to determine if the player should be extended or not
   */
  bool isExtended();

 private
slots:
  /**
   * Should be called once the animation timer is reset to clear the bool bit
   * appropriately
   * - Set animationLocked = false
   */
  void animationDone();

  /**
   * Should be called to keep reset the number of spaces since the last cool
   * down period
   * - Set numPressesSinceTimeReset = 0
   */
  void resetCooldownPeriod();
};

#endif  // PLAYERMODEL_H
