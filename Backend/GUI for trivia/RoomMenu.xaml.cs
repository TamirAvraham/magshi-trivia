using ServicesForTrivia;
using System.Windows;
using System.Windows.Controls;

namespace GUI_for_trivia
{
    /// <summary>
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Window
    {
        User user;
        RoomData roomData;
        public Menu(User user, RoomData roomData)
        {
            InitializeComponent();
            this.user = user;
            this.roomData = roomData;
            DataContext = this;

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

        }
    }
}
