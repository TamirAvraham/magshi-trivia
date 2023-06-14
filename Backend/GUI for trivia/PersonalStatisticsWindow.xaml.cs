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
        User user;
        public PersonalStatisticsWindow(User user)
        {
            InitializeComponent();
            this.user = user;

            username_value_label.Content = user.username;
        }
    }
}
