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
    /// Interaction logic for PersonalStatisticsWindow.xaml
    /// </summary>
    public partial class PersonalStatisticsWindow : Window
    {
        StatisticsData data;
        User user;
        public PersonalStatisticsWindow(StatisticsData data,User user)
        {
            InitializeComponent();
            this.data = data;

            username_value_label.Content = data.Username;
            total_answers_value_label.Content = data.TotalAnswers;
            correct_asnwers_value_label.Content = data.CorrectAnswers;
            total_games_value_label.Content = data.TotalGames;
            total_seconds_value_label.Content = data.TotalSeconds;

        }

        private void return_back_button_Click(object sender, RoutedEventArgs e)
        {
            var roomsMenu = new RoomsMenu(user);
            roomsMenu.Show();
            this.Close();
        }
    }
}
