using ServicesForTrivia;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace GUI_for_trivia
{
    /// <summary>
    /// Interaction logic for GameResultsWindow.xaml
    /// </summary>
    public partial class GameResultsWindow : Window
    {
        List<QuestionCommunicator.GameResult> results;
        User user;
        RoomData roomData;

        public GameResultsWindow(List<QuestionCommunicator.GameResult> gameData, User currentUser,RoomData roomData)
        {
            InitializeComponent();
            this.user = currentUser;
            
            this.roomData = roomData;
            foreach (var player in gameData)
            {
                players_list.Items.Add(player.ToString());
            }
            results = gameData;
        }

        public void return_back_button_Click(object sender, RoutedEventArgs e)
        {
            Window win = user.isAdmin ? new AdminControlRoomWindow(user, roomData) : new RoomView(user, roomData);
            win.Show();
            this.Close();
        }
    }
}
