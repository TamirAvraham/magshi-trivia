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
    /// Interaction logic for RecordsTableWindow.xaml
    /// </summary>
    public partial class RecordsTableWindow : Window
    {
        User user;
        public RecordsTableWindow(User user)
        {
            InitializeComponent();
            this.user = user;

            List<GameData> data = StatisticsCommunicator.GetTopFive();

            if (data.Count > 0)
            {
                number_one_username.Content = data[0].Username;
                number_one_score.Content = data[0].Points;

                number_one_place.Visibility = Visibility.Visible;
                number_one_score.Visibility = Visibility.Visible;
                number_one_username.Visibility = Visibility.Visible;
            }
            if(data.Count > 1)
            {
                number_two_username.Content = data[1].Username;
                number_two_score.Content = data[1].Points;

                number_two_place.Visibility = Visibility.Visible;
                number_two_score.Visibility = Visibility.Visible;
                number_two_username.Visibility = Visibility.Visible;
            }
            if (data.Count > 2) 
            {
                number_three_username.Content = data[2].Username;
                number_three_score.Content = data[2].Points;

                number_three_place.Visibility = Visibility.Visible;
                number_three_score.Visibility = Visibility.Visible;
                number_three_username.Visibility = Visibility.Visible;
            }
            if (data.Count > 3)
            {
                number_four_username.Content = data[3].Username;
                number_four_score.Content = data[3].Points;

                number_four_place.Visibility = Visibility.Visible;
                number_four_score.Visibility = Visibility.Visible;
                number_four_username.Visibility = Visibility.Visible;
            }
            if (data.Count > 4)
            {
                number_five_username.Content = data[4].Username;
                number_five_score.Content = data[4].Points;

                number_five_place.Visibility = Visibility.Visible;
                number_five_score.Visibility = Visibility.Visible;
                number_five_username.Visibility = Visibility.Visible;
            }
        }

        private void return_back_button_Click(object sender, RoutedEventArgs e)
        {
            var win = new RoomsMenu(user);
            win.Show();
            this.Close();
        }
    }
}
