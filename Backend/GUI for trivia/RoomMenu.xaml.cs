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
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class RoomView : Window
    {
        readonly User user;
        RoomData roomData;
        List<User> users = new List<User>();
        Timer timer;
        public RoomView(User user, RoomData roomData)
        {
            InitializeComponent();
            this.user = user;
            this.roomData = roomData;
            DataContext = this;

            room_name_label.Content = roomData.name;
            number_of_time_for_question_label_Copy.Content = $"Time Per Question: {roomData.TimePerQuestion} sec";
            questions_count.Content = $"Question Count:{roomData.numOfQuestions}";
            players_label.Content = $"players(max :{roomData.maxNumOfPlayers} ):";

            var roomState = RoomMemberComunicator.GetRoomState(roomData.id);
            foreach (var playerName in roomState.players)
            {
                User newUser = new User(playerName);
                users.Add(newUser);
                players_list.Items.Add(GeneratePlayerComponent(newUser));
            }
            
            //timer = new Timer(state =>
            //{
            //    this.Refresh();
            //}, null, TimeSpan.Zero, TimeSpan.FromSeconds(3));
        }

        /*
         * ListBox.ItemTemplate>
                <DataTemplate>
                    <Grid>
                        <Grid.ColumnDefinitions>
                            <ColumnDefinition Width="Auto" />
                            <!-- Button column -->
                            <ColumnDefinition Width="*"/>
                            <!-- Label column -->
                        </Grid.ColumnDefinitions>

                        <!-- Button -->
                        <Button Width="20" Height="20" Click="Button_Click">
                            <!-- Button content -->
                        </Button>

                        <!-- Label -->
                        <Label Grid.Column="1" Content="{Binding username}" />

                        <!-- Statistics ListBox (hidden by default) -->
                        <ListBox Grid.ColumnSpan="2" Visibility="Collapsed">
                            <!-- Statistics ListBox items -->
                        </ListBox>
                    </Grid>
                </DataTemplate>
            </ListBox.ItemTemplate>
         */
        private object GeneratePlayerComponent(User user)
        {
            var ret = new Grid();

            var column1 = new ColumnDefinition();
            column1.Width = GridLength.Auto;

            var column2 = new ColumnDefinition();
            column2.Width = new GridLength(1, GridUnitType.Star);

            ret.ColumnDefinitions.Add(column1);
            ret.ColumnDefinitions.Add(column2);

            var label = new Label();
            label.Content = user.username;

            var button = new Button();
            button.Width = 20;
            button.Height = 20;
            button.Click += (object sender, RoutedEventArgs e) => { }; //this is the part for statistics

            Grid.SetColumn(label, 1);
            ret.Children.Add(button);
            ret.Children.Add(label);

            return ret;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (RoomComunicator.JoinRoom(user.username,roomData.id))
                {
                    join_room_button.IsEnabled = false;
                    join_room_button.Background = Brushes.Red;
                    players_list.Items.Add(GeneratePlayerComponent(user));
                }
                else
                {
                    System.Console.WriteLine("error cant join room");
                }
            }
            catch (System.Exception error)
            {
                string data = error.Message;
                System.Console.WriteLine(error.Message);
            }
        }

        private void Refresh()
        {
            var roomState = RoomMemberComunicator.GetRoomState(roomData.id);
            users.Clear();
            players_list.Items.Clear();
            foreach (var playerName in roomState.players)
            {
                User newUser = new User(playerName);
                users.Add(newUser);
                players_list.Items.Add(GeneratePlayerComponent(newUser));
            }

        }
    }
}
