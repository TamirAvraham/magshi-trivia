using ServicesForTrivia;
using System;
using System.Collections.Generic;
using System.Threading;
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
        Timer timer;
        private void Click_handler(object sender, RoutedEventArgs e)
        {
            var room = (RoomData)((Button)sender).Tag;
            RoomComunicator.JoinRoom(user.username, room.Id);
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
                roomButton.Content = room.Name;
                roomButton.Tag = room;
                roomButton.Background = room.IsActive ? Brushes.Red : Brushes.Green;
                roomButton.Tag=room;
                rooms_list.Items.Add(roomButton);
            }
        }
        public RoomsMenu(User user)
        {
            InitializeComponent();
            this.user = user;
            rooms = RoomComunicator.GetRooms(Communicator.Instance);

            initRoomsList();    // Added this line because someone forgot to
            //timer = new Timer(state =>
            //{
            //    this.Refresh();
            //}, null, TimeSpan.Zero, TimeSpan.FromSeconds(3));
        }

        private void create_room_Click(object sender, RoutedEventArgs e)
        {
            var win = new CreateRoomWindow(user);
            win.Show();
            this.Close();
        }
        void Refresh()
        {
            rooms = RoomComunicator.GetRooms(Communicator.Instance);
            initRoomsList();
        }

        private void my_stats_button_Copy_Click(object sender, RoutedEventArgs e)
        {
            var stats = StatisticsCommunicator.GetPlayerStatistic(user.username);
            var personalStatisticsWindow = new PersonalStatisticsWindow(stats,user);
            personalStatisticsWindow.Show();
            this.Close();

        }

        private void top_5_button_Click(object sender, RoutedEventArgs e)
        {
            var topFIveList = StatisticsCommunicator.getTopFive();
            var win = new RecordsTableWindow(topFIveList, user);
            win.Show();
            this.Close();
        }
    }
}
