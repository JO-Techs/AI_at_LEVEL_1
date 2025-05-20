import json
import datetime
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# ===============================  SUPPORT FUNCTIONS  =======================================
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#Loading the indents file for responses
def load_intents(filename):
    with open(filename,'r',encoding='utf-8') as file:
        return json.load(file)

#Logging the conversation between user and CHABO
def log_conversation(user_input,CHABO_response):
    with open("CHABO_conversations.txt","a",encoding='utf-8') as log_file:
        time_stamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        log_file.write(f"{time_stamp} | User: {user_input}\n")
        log_file.write(f"{time_stamp} | CHABO: {CHABO_response}\n")
        
#Handling inputs not in intends file
def unknown_input():
    unknown_input_response="Could you try asking differently... I could not process this."
    return unknown_input_response

def clean_text(text):
    return text.lower().strip().split()

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# ===============================  MAIN CHABO THINGS  =======================================
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class NLPCHABO:
    def __init__(self,intents_path):
        self.intents = load_intents(intents_path)
        self.vectorizer = CountVectorizer(tokenizer=clean_text, binary=True)
        self.classifier = MultinomialNB()
        self.train_data()
        print("Training Completed")

    def train_data(self):
        self.texts = []
        self.labels = []
        for intent in self.intents['intents']:
            for pattern in intent['patterns']:
                self.texts.append(pattern)
                self.labels.append(intent['tag'])
        self.X = self.vectorizer.fit_transform(self.texts)
        self.classifier.fit(self.X, self.labels)
        self.tags = [intent['tag'] for intent in self.intents['intents']]

    def predict_intent(self, user_input):
        x_test = self.vectorizer.transform([user_input])
        probability_of_intent = self.classifier.predict_proba(x_test)[0]
        intent_with_max_prob = max(probability_of_intent)
        best_intent = self.classifier.classes_[probability_of_intent.argmax()]
        if intent_with_max_prob < 0.4:
            return None
        return best_intent
    
    def make_response(self, user_input):
        best_intent = self.predict_intent(user_input)
        if best_intent is None:
            return unknown_input()
        for intent in self.intents['intents']:
            if intent['tag'] == best_intent:
                response = intent['responses']
                log_conversation(user_input, response)
                return response