using ServicesForTrivia;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace GUI_for_trivia
{
    /// <summary>
    /// Interaction logic for RoomsMenu.xaml
    /// </summary>
    public partial class RoomsMenu : Window
    {
        List<RoomData> rooms;
        User user;
        private void Click_handler(object sender, RoutedEventArgs e)
        {
            var room = (RoomData)sender;
            var window = new RoomView(user, room);
            window.Show();
            this.Close();
        }
        private void initRoomsList()
        {
            foreach (var room in rooms)
            {
                var roomButton = new Button();
                roomButton.Click += Click_handler;
                roomButton.Content = room.name;
                roomButton.Tag = room;
                roomButton.Background = room.isActive ? Brushes.Red : Brushes.Green;
                rooms_list.Items.Add(roomButton);
            }
        }
        public RoomsMenu(User user)
        {
            InitializeComponent();
            this.user = user;
            rooms = RoomComunicator.GetRooms();

            initRoomsList();    // Added this line because someone forgot to
        }

        private void create_room_Click(object sender, RoutedEventArgs e)
        {
            var win = new CreateRoomWindow(user);
            win.Show();
            this.Close();
        }
    }
}
