# media_player
mp3 and mp4 player

Application does the following:
- Plays video and audio files stored in mp3 and mp4 media containers.
- Indexes media files of supported formats at user computer at background thread when starting application.
- Enables to search media within library and add new files.
- Show available media file data in the library.
- Support media player controls:
    - Play, Pause;
    - Rewind/Fast forward;
    - Seek;
    - Repeat mode;
    - Progress;
- Enables to create playlists with existing media files.
- Compiles for Linux and Windows;
- Non-blocking UI – does not freeze while using the app;

The application is built using Qt for UI and standard C/C++ libraries.


MAIN WINDOW CLASS

Description
The MainWindow class provides the main application window for managing media playback, libraries, and playlists.

Constructor
MainWindow(QWidget* parent = nullptr): The constructor for the MainWindow class. It initializes the main window and sets up the user interface elements.

Destructor
~MainWindow(): The destructor for the MainWindow class. It cleans up resources and handles application shutdown.

Public Member Variables
Media_thread* trd: A pointer to the Media_thread class, which is responsible for discovering available media files.

Private Member Variables
Ui::MainWindow* ui: User interface elements managed by Qt Designer.
QMediaPlayer* Player: The media player for playback.
QVideoWidget* Video: Video widget for video playback.
QAudioOutput* Audio: Audio output for audio playback.
bool is_Pause: Indicates whether media playback is paused.
bool is_Muted: Indicates whether media is muted.
QMediaPlaylist* Playlist: Playlist for managing media files.
int Play_list_index: Index of the current media item in the playlist.
int Play_list_size: Total number of media items in the playlist.
QSqlDatabase media_libs: Database for managing media libraries.
QModelIndex media_lib_index: Index of the current media library.
QModelIndex media_index: Index of the selected media item in a library.

Slots:
on_get_available_media(QString file): A slot function that is called when new media files are discovered by the Media_thread.
onTableClicked(const QModelIndex &index): Identifies the library for the specific table cell clicked by retrieving its' index. Then identifies it's name by the index and calls show_media_in_curr_lib(cellText) function to show media in this library.
onCurrentMusicIndexChanged(): Highlights mediafile name when it's playing.
on_actionOpen_video_triggered(): Opens a dialog window to choose mp4 format files from user's computer and adds them to the playlist.
on_horizontalSlider_Duration_valueChanged(int value): Implements the playlist's seek slider.
on_pushButton_Play_Pause_clicked(): Resumes or pauses current media.
on_pushButton_Stop_clicked(): Stops current media and let's play it from the start.
on_pushButton_Volume_clicked(): Media volume on/off.
on_horizontalSlider_Volume_valueChanged(int value): Sets volume value.
on_actionOpen_music_triggered(): Opens a dialog window to choose mp3 format files from user's computer and adds them to the playlist.
on_pushButton_Seek_Forward_clicked(): Plays the next to current mediafile in the playlist.
on_pushButton_Seek_Backward_clicked(): Plays the previous to current mediafile in the playlist.
on_Add_media_clicked(): Opend a dialog window and allows to add media to selected library.
on_Add_library_clicked(): Add a new library.
on_save_new_lib_clicked(): Saves library name that was previously written in the text field (new_lib_input) and allows user to choose a media file to add to it and saves this to the database.
on_new_lib_add_cancel_clicked(): Cancels a new lib addition.
on_get_available_media(QString file): Prints available on local computer media to the availabe_media list.
on_search_media_clicked(): Shows search field, search confirmation button and search cancellation when clicked.
on_search_cancel_clicked(): Cancels the search withing a chosen library.
on_search_clicked(): Searches for the file in the database and prints it to media_in_current_lib list.

Other functions:
show_media_libs(): Shows all media libraries names from the database to choose from.
show_media_in_curr_lib(QString cellText): Shows media in a chosen library.
add_to_playlist(QString qry_res): Adds a media file to the playlist.
add_from_lib_to_playlist(): calls add_to_playlist(QString qry_res) and passes a chosen library name to it.


MEDIA THREAD CLASS

Description
The constructor for the Media_thread class, which initializes the media discovery thread.

Public member variables
Media_thread* trd = new Media_thread(this) : A pointer to the parent QObject. Default is nullptr.

Public functions
void run(): It's a core function for the media discovery thread that calls platform-specific functions to discover available media files.
get_available_media_windows(): A function that discovers available media files on the Windows platform. It iterates through directories and emits a signal for each discovered media file.
get_available_media_linux(const char* dirname): A function that discovers available media files on the Linux platform. It recursively traverses directories and emits a signal for each discovered media file with extensions "mp3" or "mp4".
 
Signals

get_available_media(QString file): A signal emitted when a new media file is discovered during media discovery. It sends the file path as a QString.
