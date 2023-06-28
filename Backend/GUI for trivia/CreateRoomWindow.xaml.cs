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
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        static int id = 0;
        User user;
        public CreateRoomWindow(User user)
        {
            InitializeComponent();
            this.user = user;
        }
        RoomData proceesData()
        {
            var q_t = ((int)q_time.Value);
            var q_c = ((int)q_count.Value);
            var p_c = ((int)part_count.Value);
            var users = new List<User>();
            users.Add(user);
            var name = room_name_text_box.Text;
            return new RoomData(0, name, id++, q_t, q_c, p_c);

        }

        private void create_room_button_Click(object sender, RoutedEventArgs e)
        {
            var data = proceesData();
            int newId = RoomComunicator.CreateRoom(data, user);
            if (newId>-1)
            {
                data.id = newId;
                var win = new AdminControlRoomWindow(user, data);

                win.Show();
                this.Close();
            }
            
        }
    }
}
