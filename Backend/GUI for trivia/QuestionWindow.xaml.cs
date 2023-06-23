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
using System.Windows.Threading;

namespace GUI_for_trivia
{
    /// <summary>
    /// Interaction logic for QuestionWindow.xaml
    /// </summary>
    public partial class QuestionWindow : Window
    {
        const byte amountOfQuestions = 10;
        const byte secondsPerQuestion = 10;

        int roomId;

        int questionsCount;
        QuestionData currentQuestion;
        int correctAnswerCount;

        int totalSecondsCount = 0;
        int questionSecondsCount = 0;
        DispatcherTimer timer;        

        User user;
        public QuestionWindow(User user, int roomId)
        {
            InitializeComponent();
            this.user = user;
            questionsCount = 0;
            correctAnswerCount = 0;
            this.roomId = roomId;

            correct_answers_label.Content = 0;
            question_left_label.Content = amountOfQuestions;
            showNewQuestion();
            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += (object sender, EventArgs e) => Refresh();
            timer.Start();
            
        }


        private void showNewQuestion()
        {
            if (questionsCount == amountOfQuestions)
            {
                var roomState = RoomMemberComunicator.GetRoomState(roomId);
                var win = new GameResultsWindow(roomState.Players, user);
                win.Show();
                this.Close();
            }
            currentQuestion = QuestionCommunicator.GetQuestion(user.username);
            questionsCount++;
                
            quesiton_label.Content = currentQuestion.Question;
            answer_1_label.Content = currentQuestion.AllAnswers[0];
            answer_2_label.Content = currentQuestion.AllAnswers[1];
            answer_3_label.Content = currentQuestion.AllAnswers[2];
            answer_4_label.Content = currentQuestion.AllAnswers[3];

            correct_answers_label.Content = "Correct Answers: " + correctAnswerCount;
            question_left_label.Content = "Questions Left: " + (amountOfQuestions - questionsCount);
            
            questionSecondsCount = 0;
        }
        private void Refresh()
        {
            questionSecondsCount++;
            totalSecondsCount++;
            time_left_label.Content = "Seconds: " + (secondsPerQuestion - questionSecondsCount);
            if (int.Parse(time_left_label.Content.ToString()) <= 0)
            {
                questionsCount = 0;
                time_left_label.Content = secondsPerQuestion;
                showNewQuestion();
            }
        }
        private void asnwer_1_click(object sender, RoutedEventArgs e)
        {
            if(answer_1_label.Content == currentQuestion.CorrectAnswer)
                correctAnswerCount++;
            showNewQuestion();
        }
        private void answer_2_click(object sender, RoutedEventArgs e)
        {
            if (answer_2_label.Content == currentQuestion.CorrectAnswer)
                correctAnswerCount++;
            showNewQuestion();
        }
        private void answer_3_click(object sender, RoutedEventArgs e)
        {
            if (answer_3_label.Content == currentQuestion.CorrectAnswer)
                correctAnswerCount++;
            showNewQuestion();
        }
        private void asnwer_4_click(object sender, RoutedEventArgs e)
        {
            if (answer_4_label.Content == currentQuestion.CorrectAnswer)
                correctAnswerCount++;
            showNewQuestion();
        }


    }
}
