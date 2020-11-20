#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QKeyEvent>


namespace Ui {
class GameDialog;
}

/**
 * Window that houses the game play.
 * Used on both the Host and the Guest to display the map, info, and such in the
 * game.
 */
class GameDialog : public QDialog {
  Q_OBJECT

 public:
  /**
   * Constructor used to dynamically allocate memory
   * @param parent
   */
  explicit GameDialog(QWidget* parent = nullptr);

  /**
   * Destructor used to deallocate memory
   */
  ~GameDialog();

 private:
  Ui::GameDialog* ui;

 protected:
  /**
   * @brief A Key Press Event handler (will be used for escape)
   * @param key
   */
  void keyPressEvent(QKeyEvent* key);

signals:
  /**
   * Informs FlowChamp that the user has pressed the space bar
   */
  void GDSpacePressed();

  /**
   * Informs FlowChamp that the user has pressed the escape key
   */
  void GDEscPressed();

  /**
   * Informs FlowChamp that the user desires to leave the game
   * @deprecated
   */
  void GDQuitGame();

 public
slots:
  /**
   * Slot to be triggered when
   */
  void HandleInfoIn(/*TBD*/);
};

#endif  // GAMEDIALOG_H
