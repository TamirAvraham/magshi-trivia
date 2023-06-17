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
        List<(string, int)> records;
        public RecordsTableWindow(List<(string,int)> records,User user)
        {
            InitializeComponent();
            this.records = records;
            this.user = user;
            switch (records.Count)
            {
                case 5:
                    number_five_usernamel.Content = records[4].Item1;
                    number_five_score.Content = records[4].Item2;
                    goto case 4;
                case 4:
                    number_four_usernamel.Content = records[3].Item1;
                    number_four_score.Content = records[3].Item2;
                    goto case 3;
                case 3:
                    number_three_usernamel.Content = records[2].Item1;
                    number_three_score.Content = records[2].Item2;
                    goto case 2;
                case 2:
                    number_two_score.Content = records[1].Item2;
                    number_two_usernamel.Content = records[1].Item1;
                    goto case 1;
                case 1:
                    number_one_usernamel.Content = records[0].Item1;
                    number_one_score.Content = records[0].Item2;
                    break;
                default:
                    if (records.Count>5)
                    {
                        goto case 5;
                    }
                    break;
            }
        }

        private void return_back_button_Click(object sender, RoutedEventArgs e)
        {
            var rooms = new RoomsMenu(user);
            rooms.Show();
            this.Close();
        }
    }
}
