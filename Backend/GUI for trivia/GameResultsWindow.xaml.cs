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
        int roomId;
        

        public GameResultsWindow(List<QuestionCommunicator.GameResult> gameData, User currentUser,int roomId)
        {
            InitializeComponent();
            this.user = currentUser;
            this.roomId = roomId;

            foreach (var player in gameData)
            {
                players_list.Items.Add(player.ToString());
            }
        }

        public void return_back_button_Click(object sender, RoutedEventArgs e)
        {
            RoomData? roomData = RoomComunicator.GetRoom(roomId)!;
            var win = new RoomView(user, roomData);
        }
    }
}
