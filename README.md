# K-Match
**Authors:** [Andy Tran](https://github.com/ATranZone), [Justin Figueroa](https://github.com/jstnf), [Nathan Nguyen](https://github.com/nateknguyen) 

## Project Description
### Purpose
**K-Pop**, or Korean pop music, is an umbrella of various genres of pop music that originate from South Korea. Although K-Pop music is listened to very widely around the world, there are currently no music platforms that focus solely on this subset of music aside from all-encompassing platforms such as *Pandora* or *Spoify*. We wanted to create an application that would help new listeners catalogue and discover Korean music and artists that are similar to their tastes.
  
### Tools, Languages, and Technologies
 * [**Microsoft Visual Studio Code**](https://code.visualstudio.com/)
   * IDE used by all project members
 * **C++**
   * Using a command line main menu
   * The backend of the project
   * In-charge of multiple tasks, including rendering JavaScript, performing algorithms for recommendations, and interacting with an online database
 * **MySQL** (or other database, such as flatfile)
   * Stores all user information, including user's song lists, relationships between songs (we use these to create recommendations), and more
   * Contains songs grabbed from *Spotify* using Spotify's HTTP API

### Input/Output
Initial input is grabbed from large volumes of K-Pop music that are pre-catalogued in large release playlists on the platform *Spotify*. Song information from these lists is stored in our database for use by our application.

Using this information, users can create their own accounts on our application, granting them their own song list. Users will initially be asked to choose songs or artists that they like in order to further recommend the user more songs.

Our application will include three main displays - **search** for music in our database, **view user information** such as saved song and artist lists, and a **question-and-answer recommendation** page where users are asked questions in order to further recommend them new songs to listen to.

### Design Patterns
 1) **Strategy** -
	   We chose the strategy design pattern to have our clients not  know specifically how our C++ code would communicate with our database of recommended songs. The feature that we can implement with this design pattern allows us to establish relationships between songs even if the user does not know specific details about the songs that they provide to our program. Strategy allows the use of a context related request from a client to the proper algorithm to recommend similar songs to what the user has inputted. 
 2) **Composite** -
	     We chose the composite design pattern to have a song group as our main composite which will then contain leaves and other song groups that can hold more precise information of the recommended songs. Subclasses of the song group can contain information like the band name, release year, and even song length to the user. We will a have a client that can manipulate objects through the interface.
 3) **Chain of Responsibility** -
	    We chose chain of responsibility design pattern to have the user's input be received by the correct object to perform the correct actions on their input. This would allow our user interface to have multiple options presented to the user then depending on which input is chosen, can be passed on to the correct receiver to deal with user's request. This design pattern simplifies the objects interconnections to one another by having objects only have a single reference to their succeeding receiver. 
 
## Class Diagram
Our class diagram can be found on Google Drawings [**here**](https://docs.google.com/drawings/d/1TQYnSn7FgYnl15Sm2pPkMWSKl794P39TJgWWgG1dlOk/).

## Screenshots
 [**Example Input and Output with the Main Menu**](https://drive.google.com/file/d/1yLHeI__ZnOB-oYXIHFLWQxDeNWG9ApDc/view?usp=sharing)
 
## Installation/Usage
 1) Download repository as zip along with kmatch_files [**here**](https://drive.google.com/file/d/10wGPB69J7lD7MQI1f1WxnTzN_BR_sfcH/view?usp=sharing)
 2) Run cmake .
 4) Run make
 5) Run the created kmatch.exe with the files in kmatch_files in the same directory
 6) You are first prompted to enter a username to create a profile for you 
 7) You are then prompted with the main menu which you can navigate with the on screen prompts
## Testing
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.
