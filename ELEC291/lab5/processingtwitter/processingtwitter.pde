

static String OAuthConsumerKey = "HqJInxj5AGTHV781lbEwtg3WG";
static String OAuthConsumerSecret = "leSLKvnJWMmnQccBVMl1lTpVDHv6BYeVrGMEo1eEzyBKnpwVPw";
static String AccessToken = "695289997314756608-uKSTvy51TmIOWxh3ouVzEYFhbvhZ3Gk";
static String AccessTokenSecret = "6U9RAv8R42t7hne04o7uQsgGQwKEuqnZWRAXhoRmoG9Se";


// Just some random variables kicking around
String myTimeline;
java.util.List statuses = null;
User[] friends;
Twitter twitter = new TwitterFactory().getInstance();
RequestToken requestToken;
String[] theSearchTweets = new String[11];


void setup() {
  
  size(100,100);
  background(0);
  
  connectTwitter();
  
  
}


void draw() {
  while (myPort.available() > 0) {
    String inBuffer = myPort.readString();   
    if (inBuffer=="out of range") {
      sendTweet("Your distance is out of range");
    }
  
  background(0);
  
}


// Initial connection
void connectTwitter() {

  twitter.setOAuthConsumer(OAuthConsumerKey, OAuthConsumerSecret);
  AccessToken accessToken = loadAccessToken();
  twitter.setOAuthAccessToken(accessToken);

}

// Sending a tweet
void sendTweet(String t) {

  try {
    Status status = twitter.updateStatus(t);
    println("Successfully updated the status to [" + status.getText() + "].");
  } catch(TwitterException e) { 
    println("Send tweet: " + e + " Status code: " + e.getStatusCode());
  }

}


// Loading up the access token
private static AccessToken loadAccessToken(){
  return new AccessToken(AccessToken, AccessTokenSecret);
}