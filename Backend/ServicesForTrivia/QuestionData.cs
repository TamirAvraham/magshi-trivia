﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    
    public struct QuestionData
    {
        [JsonPropertyName("question")]
        public string Question { get; set; }

        [JsonPropertyName("answers")]
        public List<string> AllAnswers { get; set; }

    }
}