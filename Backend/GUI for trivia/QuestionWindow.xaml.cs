
using System;
using System.Collections.Generic;
using System.ComponentModel;
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
using ServicesForTrivia;
namespace GUI_for_trivia
{
    /// <summary>
    /// Interaction logic for QuestionWindow.xaml
    /// </summary>
    public partial class QuestionWindow : Window
    {
        
        

        int roomId;
        int gameId;
        int questionsCount;
        QuestionData currentQuestion;
        int correctAnswerCount;
        RoomData roomData;
        int totalSecondsCount = 0;
        int questionSecondsCount = 0;
        bool send = true;
        DispatcherTimer timer;        

        User user;
        public QuestionWindow(User user, int roomId,int gameId,RoomData roomData)
        {
            InitializeComponent();
            questionsCount = 0;
            correctAnswerCount = 0;

            this.user = user;
            this.roomId = roomId;
            this.gameId = gameId;
            this.roomData = roomData;

            correct_answers_label.Content = 0;
            question_left_label.Content = roomData.NumOfQuestions;

            showNewQuestion();

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += (object sender, EventArgs e) => Refresh();
            timer.Start();

        }


        private void showNewQuestion()
        {
            if (questionsCount == roomData.NumOfQuestions)
            {
                var results = QuestionCommunicator.GetGameResults(gameId,user.username);
                var win = new GameResultsWindow(results, user,roomData);
                win.Show();
                this.Close();
                return;
            }

            currentQuestion = QuestionCommunicator.GetQuestion(user.username, gameId);
            if (currentQuestion.Question=="" || currentQuestion.Question == null)
            {
                
                var results = QuestionCommunicator.GetGameResults(gameId, user.username);
                var win = new GameResultsWindow(results, user, roomData);
                win.Show();
                this.Close();
                return;
            }
            questionsCount++;
            
            quesiton_label.Content = currentQuestion.Question;
            answer_1_label.Content = currentQuestion.AllAnswers[0];
            answer_2_label.Content = currentQuestion.AllAnswers[1];
            answer_3_label.Content = currentQuestion.AllAnswers[2];
            answer_4_label.Content = currentQuestion.AllAnswers[3];

            correct_answers_label.Content = "Correct Answers: " + correctAnswerCount;
            question_left_label.Content = "Questions Left: " + (roomData.NumOfQuestions - questionsCount);
            
            questionSecondsCount = 0;
        }
        private void Refresh()
        {
            questionSecondsCount++;
            totalSecondsCount++;
            time_left_label.Content = "Seconds: " + (roomData.TimePerQuestion - questionSecondsCount);
            if (int.Parse(time_left_label.Content.ToString()!.Replace("Seconds: ","")) <= 0)
            {
                questionsCount = 0;
                time_left_label.Content = roomData.TimePerQuestion;
                showNewQuestion();
            }
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            timer.Stop();
            base.OnClosing(e);
            
        }

        private void HandleAnswer(object sender, RoutedEventArgs e)
        {
            try
            {
                Button button = (Button)sender;
                var correctAnswer = QuestionCommunicator.SubmitAnswer(currentQuestion.Question,
                                                                      gameId,
                                                                      user.username,
                                                                      questionSecondsCount,
                                                                      button.Content.ToString()!);
                if (correctAnswer)
                {
                    correctAnswerCount++;
                }


                showNewQuestion();
            }
            catch (Exception error)
            {
                
                throw;
            }
        }
    }
}
