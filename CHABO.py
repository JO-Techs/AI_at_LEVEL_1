import json
import datetime
import random
from sklearn.feature_extraction.text import TfidfVectorizer
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
    x = text.lower().strip().split()
    return x

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# ===============================  MAIN CHABO THINGS  =======================================
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class NLPCHABO:
    def __init__(self,intents_path):
        self.intents = load_intents(intents_path)
        self.vectorizer = TfidfVectorizer (tokenizer=clean_text, token_pattern = None, lowercase = True)
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
        #print("Probabilities:", probability_of_intent)
        intent_with_max_prob = max(probability_of_intent)
        best_intent = self.classifier.classes_[probability_of_intent.argmax()]
        if intent_with_max_prob < 0.2:
            return None
        return best_intent
                           
    def make_response(self, user_input):
        intent = self.predict_intent(user_input)
        if intent:
            for i in self.intents['intents']:
                if i['tag'] == intent:
                    return random.choice(i['responses'])
        return unknown_input()
    

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# ==================================  MAIN Function  ========================================
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

def main():
    print("CHABO: Hello, I am CHABO 1.0 \n To exit type 'QUIT' or 'EXIT' \n Ask Me Something...")
    bot = NLPCHABO("intents.json")
    while True:
        user_input = input("You: ").strip()
        if user_input.lower() in ["exit","quit"]:
            print("CHABO: Exiting...")
            break
        response = bot.make_response(user_input)
        print("CHABO: ", response)
        log_conversation(user_input, response)

if __name__ == "__main__":
    main()