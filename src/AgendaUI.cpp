#include "../include/AgendaService.hpp"
#include "../include/AgendaUI.hpp"
#include <iostream>
#include <string>
#include <iomanip>
using std :: cin;
using std :: cout;
using std :: endl;
using std :: string;
using std :: list;
using std :: ios;
using std :: setw;
using std :: setiosflags;
using std :: resetiosflags;
AgendaUI :: AgendaUI() {
    m_userName = "";
    m_userPassword = "";
    startAgenda();
}
void AgendaUI :: OperationLoop(void) {
    while (true) {
        for (int i = 1 ; i <= 37; i++)
             cout << "-";
        cout << "Agenda";
        for (int i = 1 ; i <= 37; i++)
             cout << "-";
        cout << endl;
        cout << "Action :" << endl;
        if (m_userName == "") {
            cout << "l    - log in Agenda by user name and password" << endl;
            cout << "r    - register an Agenda account" << endl;
            cout << "q    - quit Agenda" << endl;
        } else {
            cout << "o    - log out Agenda" << endl;
            cout << "dc   - delete Agenda account" << endl;
            cout << "lu   - list all Agenda user" << endl;
            cout << "cm   - create a meeting" << endl;
            cout << "la   - list all meetings" << endl;
            cout << "las  - list all sponsor meetings" << endl;
            cout << "lap  - list all participator meetings" << endl;
            cout << "qm   - query meeting by title" << endl;
            cout << "qt   - query meeting by time interval" << endl;
            cout << "dm   - delete meeting by title" << endl;
            cout << "da   - delete all meetings" << endl;
        }
        for (int i = 1 ; i <= 80; i++)
            cout << "-";
        cout << endl;
        cout << endl;
        if (m_userName == "")
            cout << "Agenda :~$ ";
        else
            cout << "Agenda@" << m_userName << " :~# ";
        if (!executeOperation(getOperation()))
            break;
    }
}
void AgendaUI :: startAgenda(void) {
    system("clear");
}
std::string AgendaUI :: getOperation() {
    string s;
    cin >> s;
    return s;
}
bool AgendaUI :: executeOperation(std::string op) {
    for (int i = 0 ; i < op.length() ; i++)
        op[i] = tolower(op[i]);
    bool flag = true;
    if (m_userName == "")
        flag =false;
    if (op == "l" && !flag) {
       userLogIn();
       return true;
    }
    if (op == "r" && !flag) {
       userRegister();
       return true;
    }
    if (op == "dc" && flag) {
       deleteUser();
       return true;
    }
    if (op == "lu" && flag) {
       listAllUsers();
       return true;
    }
    if (op == "cm" && flag) {
       createMeeting();
       return true;
    }
    if (op == "la" && flag) {
       listAllMeetings();
       return true;
    }
    if (op == "las" && flag) {
       listAllSponsorMeetings();
       return true;
    }
    if (op == "lap" && flag) {
       listAllParticipateMeetings();
       return true;
    }
    if (op == "qm" && flag) {
       queryMeetingByTitle();
       return true;
    }
    if (op == "qt" && flag) {
       queryMeetingByTimeInterval();
       return true;
    }
    if (op == "dm" && flag) {
       deleteMeetingByTitle();
       return true;
    }
    if (op == "da" && flag) {
       deleteAllMeetings();
       return true;
    }
    if (op == "o" && flag) {
       userLogOut();
       return true;
    }
    if (op == "q" && !flag) {
       m_agendaService.quitAgenda();
       return false;
    }
    cout << endl;
    cout << "Please enter correct command!" << endl;
    cout << endl;
    return true;
}
void AgendaUI :: userLogIn(void) {
    cout << endl;
    cout << "[log in] [username] [password]" << endl;
    cout << "[log in] ";
    cin >> m_userName >> m_userPassword;
    if (m_agendaService.userLogIn(m_userName , m_userPassword)) {
        cout << "[log in] succeed!" << endl;
    } else {
        cout << "[log in] Password error or user doesn't exist" << endl;
        m_userName = "";
        m_userPassword = "";
    }
    cout << endl;
}
void AgendaUI :: userRegister(void) {
    cout <<  endl;
    cout << "[register] [username] [password] [email] [phone]" << endl;
    cout << "[register] ";
    string newUserName , newPassword , newEmail , newPhone;
    cin >> newUserName >> newPassword >> newEmail >> newPhone;
    if (m_agendaService.userRegister(newUserName , newPassword ,
                                      newEmail , newPhone)) {
        cout << "[register] succeed!" << endl;
    } else {
        cout << "[register] This username has been registered!" << endl;
    }
    cout << endl;
}
void AgendaUI :: quitAgenda(void) {
    m_agendaService.quitAgenda();
}
void AgendaUI :: userLogOut(void) {
    m_userName = "";
    m_userPassword = "";
    cout << endl;
    cout << endl;
}
void AgendaUI :: deleteUser(void) {
    cout << endl;
    m_agendaService.deleteUser(m_userName , m_userPassword);
    m_userName = "";
    m_userPassword = "";
    cout << "[delete agenda account] succeed!" << endl;
    cout << endl;
}
void AgendaUI :: listAllUsers(void) {
    cout << endl;
    cout << "[list all users] " << endl;
    cout << endl;
    cout << setiosflags(ios :: left);
    cout << setw(8) << "name";
    cout << setw(16) << "email";
    cout << "phone" << endl;
    list<User> l;
    l = m_agendaService.listAllUsers();
    list<User> :: iterator it = l.begin();
    while (it != l.end()) {
        cout << setw(8) << it -> getName();
        cout << setw(16) << it -> getEmail();
        cout << it -> getPhone() << endl;
        it++;
    }
    cout << resetiosflags(ios :: left);
    cout << endl;
}
void AgendaUI :: createMeeting(void) {
    cout << endl;
    cout << "[create meeting] [title] [participator] " 
         << "[start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" 
         << endl;
    cout << "[create meeting] ";
    string participator , sTime , eTime , title;
    cin >> title >> participator >> sTime >> eTime;
    if (m_agendaService.createMeeting(m_userName , title , participator,
                                     sTime , eTime)) {
        cout << "[create meeting] succeed!" << endl;
    } else {
        cout << "[create meeting] error!"<< endl;
    }
    cout << endl;
}
void AgendaUI :: listAllMeetings(void) {
    list<Meeting> l(m_agendaService.listAllMeetings(m_userName));
    //auto l = m_agendaService.listAllMeetings(m_userName);
    cout << endl;
    cout << "[list all meetings]" << endl;
    cout << endl;
    if (l.empty()) {
        cout << "None" << endl;
        cout << endl;
    } else {
        printMeetings(l);
    }
}
void AgendaUI :: listAllSponsorMeetings(void) {
    cout << endl;
    cout << "[list all sponsor meetings]" << endl;
    list<Meeting> l(m_agendaService.listAllSponsorMeetings(m_userName));
    //auto l = m_agendaService.listAllSponsorMeetings(m_userName);
    cout << endl;
    if (l.empty()) {
        cout << "None" << endl;
        cout << endl;
    } else {
        printMeetings(l);
    }
}
void AgendaUI :: listAllParticipateMeetings(void) {
    list<Meeting> l(m_agendaService.listAllParticipateMeetings(m_userName));
    //auto l = m_agendaService.listAllParticipateMeetings(m_userName);
    cout << endl;
    cout << "[list all participator meetings]" << endl;
    cout << endl;
    if (l.empty()) {
        cout << "None" << endl;
        cout << endl;
    } else {
        printMeetings(l);
    }
}
void AgendaUI :: queryMeetingByTitle(void){
    cout << endl;
    cout << "[query meeting] [titel]:" << endl;
    string title;
    cout << "[query meeting] ";
    cin >> title;
    list<Meeting> l(m_agendaService.meetingQuery(m_userName , title));
    //auto l = m_agendaService.meetingQuery(m_userName , title);
    if (l.empty()) {
        cout << "None" << endl;
        cout << endl;
        return;
    }
    cout << endl;
    cout << setiosflags(ios :: left);
    cout << setw(15) << "sponsor";
    cout << setw(15) << "participator";
    cout << setw(18) << "start time";
    cout << "end time";
    cout << endl;
    list<Meeting> :: iterator it = l.begin();
    while (it != l.end()) {
        cout << setw(15) << it -> getSponsor();
        cout << setw(15) << it -> getParticipator();
        cout << setw(18) << Date :: dateToString(it -> getStartDate());
        cout << Date :: dateToString(it -> getEndDate());
        cout << endl;
        it++;
    }
    cout << resetiosflags(ios :: left);
    cout << endl;
}
void AgendaUI :: queryMeetingByTimeInterval(void) {
    cout << endl;
    cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] "
         << "[end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[query meetings] ";
    string sTime , eTime;
    cin >> sTime >> eTime;
    cout << endl;
    cout << "[query meetings]" << endl;
    list<Meeting> l(m_agendaService.meetingQuery(m_userName , sTime , eTime));
    //l = m_agendaService.meetingQuery(m_userName , sTime , eTime);
    cout << endl;
    if (l.empty()) {
        cout << "None" << endl;
        cout << endl;
    } else {
        printMeetings(l);
    }
}
void AgendaUI :: deleteMeetingByTitle(void) {
    cout << endl;
    cout << "[delete meeting] [title]" << endl;
    cout << "[delete meeting] ";
    string title;
    cin >> title;
    cout << endl;
    if (m_agendaService.deleteMeeting(m_userName , title)) {
        cout << "[delete meeting] succeed!" << endl;
    } else {
        cout << "[error] delete meeting fail!" << endl;
    }
    cout << endl;
}
void AgendaUI :: deleteAllMeetings(void) {
   cout << endl;
   if (m_agendaService.deleteAllMeetings(m_userName)) {
       cout << "[delete all meeting] succeed!" << endl;
   } else {
       cout << "[error] delete all meeting fail!" << endl;
   }
   cout << endl;
}
void AgendaUI :: printMeetings(std::list<Meeting> meetings) {
    cout << setiosflags(ios :: left);
    cout << setw(15) << "title";
    cout << setw(15) << "sponsor";
    cout << setw(15) << "participator";
    cout << setw(18) << "start time";
    cout << "end time";
    cout << endl;
    list<Meeting> :: iterator it = meetings.begin();
    while (it != meetings.end()) {
        cout << setw(15) << it -> getTitle();
        cout << setw(15) << it -> getSponsor();
        cout << setw(15) << it -> getParticipator();
        cout << setw(18) << Date :: dateToString(it -> getStartDate());
        cout << Date :: dateToString(it -> getEndDate());
        cout << endl;
       it++;
    }
    cout << resetiosflags(ios :: left);
    cout << endl;

}
