//**************
// This oraconf.cpp class is designed and created to configure
// the Ubuntu 14.04 system and install the dependancies
// for the Oracle 11gR2 databse, and the oracle user. 
// author:GeoWade
//**************
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <locale>

using namespace std;

const int MAX_INDY = 750;

struct Confstruct
{
    string silestrct;
    string prostrct;
    string limstrct;
};
struct Ssdhconstrct
{
    string strctconfssh;
    string strctssd;
    string rnstrctssd;
};
void AppInstall(list<string> pkgaddList);

void AppRem(list<string> remappList);

void ReadConfSsh(ifstream& confsshIn, Ssdhconstrct& ssdstrct);

void ConfSshPrint(ofstream& confsshOut, Ssdhconstrct& ssdstrct);

void ReadSsdh(ifstream& ssdHin, Ssdhconstrct& ssdstrct);

void SsdhPrnt(ofstream& ssdHut, Ssdhconstrct& ssdstrct);

void SsdRnRead(ifstream& bakRnSsd, Ssdhconstrct& ssdstrct);

void SsdRnPrnt(ofstream& ssdRn, Ssdhconstrct& ssdstrct);

void SileReadIn(ifstream& sctlIn, Confstruct& confstruct);

void SileBakPrint(ofstream& sctlOut, Confstruct& confstruct);

void ProfReadIn(ifstream& profIn, Confstruct& confstruct);

void ProfBakPrint(ofstream& profOut, Confstruct& confstruct);

void LimReadIn(ifstream& limIn, Confstruct& confstruct);

void LimBakPrint(ofstream& limOut, Confstruct& confstruct);

void ConfigureSsh(ofstream& ssdConf, list<string> ssdhList);

void SsdhConfigure(ifstream& ssdIn, ofstream& ssdOut);

void SsdRnScrip(ifstream& scrpRn, ofstream& rnScrp);

void SctlPrintOut(ifstream& inSctl, ofstream& outSctl, list<string> sctlconList);    
    
void ProfPrintOut(ifstream& inProf, ofstream& outProf, list<string> proList);
    
void LimPrintOut(ifstream& inLim, ofstream& outLim, list<string> limList);
  
Confstruct confstruct[MAX_INDY];

Ssdhconstrct ssdhconstrct[MAX_INDY];

int main()
{ 

    // pkgAdd array containing packages to be installed
    const static string pkgAdd[51] = {"alien ", "autoconf", "automake", 
                                      "autotools-dev", "binutils",
                                      "doxygen", "elfutils", "expat", "gawk", 
                                      "gcc", "gcc-multilib", "g++-multilib",
                                      "libstdc++6-4.8-dev", "ksh", "less", 
                                      "libtiff4-dev", "lib32z1", "lib32stdc++4.8-dev",
                                      "libaio1", "libaio-dev", "libc6-dev", 
                                      "libc6-dev-i386", "libc6-i386", 
                                      "libelf-dev", "libltdl-dev", "libmotif4",
                                      "libodbcinstq4-1", "libodbcinstq4-1:i386",
                                      "libpthread-stubs0-dev", "libpth-dev", 
                                      "libstdc++5", "libstdc++5:i386", 
                                      "lsb-cxx", "make", "pdksh", "libodbc1", 
                                      "rlwrap", "rpm", "sysstat", "unixodbc", 
                                      "unixodbc-dev", "x11-utils", "zlibc", 
                                      "libglapi-mesa:i386", "libglu1-mesa:i386", 
                                      "libqt4-opengl:i386", "libpthread-workqueue0", 
                                      "libzthread-2.3-2", "libzthread-dev",
                                      "libpthread-stubs0-dev", "openssh-server"};

    // package array for removing software
    const static string pkgRem[75] = {"transmission-gtk", "deja-dup", "vino",
                                      "empathy", "gnome-orca", "remmina", "onboard",
                                      "vino", "zeitgeist-core",
                                      "evolution-data-server",
                                      "remmina", "empathy-common", "totem-common",
                                      "gnome-online-accounts", "thunderbird",
                                      "zeitgeist", "ubuntuone-client", "whoopsie",
                                      "evolution-data-server-online-accounts",
                                      "landscape-client-ui-install", "rtkit",
                                      "whoopsie-preferences", "rsyslog", "totem",
                                      "espeak-data", "gnome-calculator",
                                      "yelp", "gnome-games-data", "gnomine", "mahjongg",
                                      "gnome-sudoku", "aisleriot", "jockey-gtk",
                                      "jockey-common", "espeak", "espeak-data",
                                      "telepathy-haze", "telepathy-mission-control-5",
                                      "telepathy-salut", "rhythmbox", "cups",
                                      "cups-browsed",
                                      "telnet", "liboverlay-scrollbar-0.2-0",
                                      "gnome-user-share",
                                      "transmission-common", "libvncserver0",
                                      "telepathy-gabble",
                                      "liboverlay-scrollbar3-0.2-0", "overlay-scrollbar",
                                      "remmina-common", "unity-voice-service",
                                      "account-plugin-salut",
                                      "account-plugin-windows-live",
                                      "account-plugin-twitter",
                                      "account-plugin-salut", "account-plugin-jabber",
                                      "account-plugin-google", "account-plugin-flickr",
                                      "account-plugin-facebook", "account-plugin-yahoo",
                                      "unity-voice-service:amd64", "speech-dispatcher",
                                      "hplip-data", "seahorse", "gnome-session",
                                      "gnome-session-fallback",
                                      "mobile-broadband-provider-info",
                                      "irqbalance", "brltty", "ntfs-3g",
                                      "libcupsppdc1", "libcupsmime1",
                                      "metacity", "zenity"};

    // An array containing the ssh/sshd configuration and script files
    const static string ssdhCnfArry[20] = {"# ssh - OpenBSD Secure Shell server\n#",
                                           "# The OpenSSH server provides secure shell access to the system.\n",
                                           "description  \"OpenSSH server\"\n",
                                           "# start on runlevel [2345]",
                                           "# stop on runlevel [!2345]\n",
                                           "respawn",
                                           "respawn limit 10 5",
                                           "umask 022\n",
                                           "env SSH_SIGSTOP=1",
                                           "expect stop\n",
                                           "# \'sshd -D\' leaks stderr and confuses things in conjunction with \'console log\'",
                                           "console none\n",
                                           "pre-start script",
                                           "    test -x /usr/sbin/sshd || { stop; exit 0; }",
                                           "    test -e /etc/ssh/sshd_not_to_be_run && { stop; exit 0; }\n",
                                           "    mkdir -p -m0000 /var/run/sshd",
                                           "end script\n",
                                           "# if you used to set SSHD_OPTS in /etc/default/ssh, you can change the",
                                           "# \'exec\' line here instead",
                                           "# exec /usr/sbin/sshd -D"};

    // An array containing the oracle user modifcations to config files
    const static string oraCnfArry[45] = {"#\n# Oracle 11g\n#",
                                          "kernel.sem = 250 32000 100 128",
                                          "kernel.shmall = 2097152",
                                          "kernel.shmmni = 4096",
                                          "# Replace kernel.shmmax with the half of your memory in bytes",
                                          "# if lower than 4Go minus 1",
                                          "# 1073741824 is 1 GigaBytes",
                                          "kernel.shmmax=1073741824",
                                          "# Try sysctl -a | grep ip_local_port_range to get real values",
                                          "net.ipv4.ip_local_port_range = 9000  65500",
                                          "net.core.rmem_default = 262144",
                                          "net.core.rmem_max = 4194304",
                                          "net.core.wmem_default = 262144",
                                          "net.core.wmem_max = 1048576",
                                          "# Max value allowed, should be set to avoid IO errors",
                                          "fs.aio-max-nr = 1048576",
                                          "# 512 * PROCESSES / what really means processes ?",
                                          "fs.file-max = 6815744",
                                          "# To allow dba to allocate hugetlbfs pages",
                                          "# 1001 is your oinstall group, id. grep oinstall /etc/group will give this value",
                                          "vm.hugetlb_shm_group = 1001",
                                          "# export ORACLE_HOME=/u001/app/oracle/Ora11gR2Db/product/11.2.0/dbhome_1",
                                          "# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ORACLE_HOME/lib",
                                          "# export PATH=$PATH:$ORACLE_HOME/bin",
                                          "# export ORACLE_SID=orcl",
                                          "# export ORACLE_UNQNAME=orcl",
                                          "# export JAVA_HOME=$ORACLE_HOME/jdk",
                                          "# export JRE_HOME=$JAVA_HOME/jre/bin\n",
                                          "# /etc/profile: system-wide .profile file for the Bourne shell (sh(1))",
                                          "# and Bourne compatible shells (bash(1), ksh(1), ash(1), ...).\n",
                                          "# The Oracle user's shell",
                                          "if [ $USER = \"oracle\" ]; then",
                                          "  if [ $SHELL = \"/bin/bash\" ]; then",
                                          "    ulimit -p 16384",
                                          "    ulimit -n 65536",
                                          "  else",
                                          "    ulimit -u 16384 -n 65536",
                                          "  fi",
                                          "fi\n",
                                          "# Oracle",
                                          "oracle           soft    nproc   	2047",
                                          "oracle           hard    nproc   	16384",
                                          "oracle           soft    nofile  	1024",
                                          "oracle           hard    nofile  	65536",
                                          "oracle           soft    stack   	10240"};

    // create the holdWord temporary variable and the lists used in the program
    string holdWord = "";
    list<string> ssdhList;
    list<string> intermList;
    list<string> sctlconList;
    list<string> proList;
    list<string> limList;
    list<string> pkgaddList;
    list<string> remappList;

    // nitialize and fill the ssdhList list
    for (int j = 0; j < 20; j++) {

          string listSsdhHold = ssdhCnfArry[j];
          holdWord = listSsdhHold;
          ssdhList.push_back(holdWord);
          holdWord = "";
    }
    // initialize and fill the intermList list
    for (int j = 0; j < 45; j++) {

          string holdList = oraCnfArry[j];
          holdWord = holdList;
          intermList.push_back(holdWord);
          holdWord = "";
    }
    // initialize and fill the sctlconList list
    for (int j = 0; j < 21; j++) {

          string listSctlcon = intermList.front();
          intermList.pop_front();
          holdWord = listSctlcon;
          sctlconList.push_back(holdWord);
          holdWord = "";
    }

    // initialize and fill the proList list
    for (int j = 0; j < 18; j++) {

          string listPro = intermList.front();
          intermList.pop_front();
          holdWord = listPro;
          proList.push_back(holdWord);
          holdWord = "";
    }

    // initialize and fill the limList list
    for (int j = 0; j < 6; j++) {

          string listLim = intermList.front();
          intermList.pop_front();
          holdWord = listLim;
          limList.push_back(holdWord);
          holdWord = "";
    }

    // fill the pkgaddList list
    for (int j = 0; j < 51; j++) {

          string applistHold = pkgAdd[j];
          holdWord = applistHold;
          pkgaddList.push_back(holdWord);
          holdWord = "";
    }
    // fill the remappList list
    for (int j = 0; j < 75; j++) {

          string remlistHold = pkgRem[j];
          holdWord = remlistHold;
          remappList.push_back(holdWord);
          holdWord = "";

    }

    // update, upgrade, and dist-upgrade using the sytem function
    system("sudo apt-get update");

    system("sudo apt-get upgrade -y");

    system("sudo apt-get dist-upgrade -y");

    // update the local database
    system("sudo updatedb");

    // install the package dependencies
    AppInstall(pkgaddList);

    // stop the ssh server
    system("sudo stop ssh");

    // update the local database
    system("sudo updatedb");

    // update the application software
    system("sudo apt-get update");

    // remove unwanted packages
    AppRem(remappList);    

    // remove dangling packages 
    system("sudo apt-get autoremove -y");
    
    system("sudo apt-get update");

    system("sudo updatedb");

    system("sudo ln -s /usr/lib/x86_64-linux-gnu /usr/lib64");

    system("sudo ln -sf /bin/bash /bin/sh");

    system("sudo ln -s /usr/bin/awk /bin/awk");

    system("sudo ln -s /usr/bin/rpm /bin/rpm");

    system("sudo ln -s /usr/bin/basename /bin/basename");

    system("cd /lib64 && sudo ln -s /lib/x86_64-linux-gnu/libgcc_s.so.1 .");


    // create the Confstruct and Ssdhconstruct object
    Confstruct confstruct[MAX_INDY];
    Ssdhconstrct ssdhconstrct[MAX_INDY];

    // create the ssh.conf back-up file
    ofstream confsshOut;
    confsshOut.open("/etc/init/ssh.conf.bak");
    ifstream confsshIn;
    confsshIn.open("/etc/init/ssh.conf");

    for (int i = 0; i < 29; i++) {

        ReadConfSsh(confsshIn, ssdhconstrct[i]);

    }
    for (int i = 0; i < 29; i++) {

        ConfSshPrint(confsshOut, ssdhconstrct[i]);

    }
    confsshIn.close();
    confsshOut.close();

    // create the sshd_config back-up file
    ofstream sshdTwo;
    sshdTwo.open("/etc/ssh/sshd_config.bak");
    ifstream sshdOne;
    sshdOne.open("/etc/ssh/sshd_config");

    for (int i = 29; i < 117; i++) {

      ReadSsdh(sshdOne, ssdhconstrct[i]);

    }

    for (int i = 29; i < 117; i++) {

      SsdhPrnt(sshdTwo, ssdhconstrct[i]);

    }

    sshdOne.close();
    sshdTwo.close();

    // create the /etc/init.d/ssh back-up file
    ofstream sshrnTwo;
    sshrnTwo.open("/etc/init.d/ssh.bak");
    ifstream sshrnOne;
    sshrnOne.open("/etc/init.d/ssh");

    for (int i = 117; i < 291; i++) {

      SsdRnRead(sshrnOne, ssdhconstrct[i]);

    }

    for (int i = 117; i < 291; i++) {

      SsdRnPrnt(sshrnTwo, ssdhconstrct[i]);

    }

    sshrnOne.close();
    sshrnTwo.close();

    // create the sysctl.conf back up file
    ofstream sctlOut;
    sctlOut.open("/etc/sysctl.conf.bak");
    ifstream sctlIn;
    sctlIn.open("/etc/sysctl.conf");

    for (int i = 0; i < 60; i++) {

        SileReadIn(sctlIn, confstruct[i]);

    }

    for (int i = 0; i < 60; i++) {

        SileBakPrint(sctlOut, confstruct[i]);

    }

    sctlIn.close();
    sctlOut.close();

    // create the /etc/profile back-up file
    ofstream profOut;
    profOut.open("/etc/profile.bak");
    ifstream profIn;
    profIn.open("/etc/profile");

    for (int i = 60; i < 90; i++) {

        ProfReadIn(profIn, confstruct[i]);

    }

    for (int i = 60; i < 90; i++) {

        ProfBakPrint(profOut, confstruct[i]);

    }

    profIn.close();
    profOut.close();

    // create the limits.conf backup file
    ofstream limOut;
    limOut.open("/etc/security/limits.conf.bak");
    ifstream limIn;
    limIn.open("/etc/security/limits.conf");

    for (int i = 90; i < 146; i++) {

        LimReadIn(limIn, confstruct[i]);

    }
    for (int i = 90; i < 146; i++) {

        LimBakPrint(limOut, confstruct[i]);

    }

    limIn.close();
    limOut.close();   

    // create the new /etc/init/ssh.conf file
    ofstream confSsh;
    confSsh.open("/etc/init/ssh.conf");
    ConfigureSsh(confSsh, ssdhList);
    confSsh.close();

    // create the new /etc/ssh/sshd_config file
    ofstream ssdOut;
    ssdOut.open("/etc/ssh/sshd_config");
    ifstream ssdIn;
    ssdIn.open("/etc/ssh/sshd_config.bak");

    SsdhConfigure(ssdIn, ssdOut);

    ssdIn.close();
    ssdOut.close();

    // create the new /etc/init.d/ssh executable script file
    ofstream sshRnOut;
    sshRnOut.open("/etc/init.d/ssh");
    ifstream sshRnIn;
    sshRnIn.open("/etc/init.d/ssh.bak");

    SsdRnScrip(sshRnIn, sshRnOut);

    sshRnIn.close();
    sshRnOut.close();

    // configure the /etc/sysctl.conf file
    ofstream outSctl;
    outSctl.open("/etc/sysctl.conf");
    ifstream inSctl;
    inSctl.open("/etc/sysctl.conf.bak");
    SctlPrintOut(inSctl, outSctl, sctlconList);
    inSctl.close();
    outSctl.close();

    // configure the /etc/profile file
    ofstream outProf;
    outProf.open("/etc/profile");
    ifstream inProf;
    inProf.open("/etc/profile.bak");
    ProfPrintOut(inProf, outProf, proList);
    inProf.close();
    outProf.close();

    // configure the /etc/security/limits.conf file
    ofstream outLim;
    outLim.open("/etc/security/limits.conf");
    ifstream inLim;
    inLim.open("/etc/security/limits.conf.bak");
    LimPrintOut(inLim, outLim, limList);
    inLim.close();
    outLim.close();

    // create the oracle user home directory
    system("sudo mkdir -p -m0755 /u001/app/oracle");

    // unzip the oracle 11gR2 database archives
    system("unzip Downloads/linux.x64_11gR2_database_1of2.zip");

    system("unzip Downloads/linux.x64_11gR2_database_2of2.zip");

    // update the local database
    system("sudo updatedb");

    // create the primary group for the oracle user
    system("sudo groupadd oinstall");

    // create the dba group for the oracle user
    system("sudo groupadd dba");

    // create the oper group for the oracle user
    system("sudo groupadd oper");

    // create the oracle user and assign groups accordingly
    system("sudo useradd -g oinstall -G dba,oper,24,27,30,46 -d /u001/app/oracle -s /bin/bash oracle");

    // set the oracle user account password
    system("perl -e \'$orac=\"oracle\" ; print \"$orac\n$orac\n\";\' | (passwd oracle)");

    // force ownership of the oracle user and primary group the oracle home directory
    system("sudo chown -R oracle:oinstall /u001/app/oracle");

    system("sudo chown -R 0775 /u001/app/oracle");

    // mv the newly extracted database file the oracle users home directory
    system("sudo mv database /u001/app/oracle/");

    // clear all the lists used in the program
    pkgaddList.clear();
    remappList.clear();
    intermList.clear();
    sctlconList.clear();
    proList.clear();
    limList.clear();
    ssdhList.clear();

    return 0;

}
void AppInstall(list<string> pkgaddList) 
{

    int pkgin = 0;
    pkgin += pkgaddList.size();

    for (int j = 0; j < pkgin; j++) {

        string holdpkg = pkgaddList.front();
        pkgaddList.pop_front();

        system(("sudo apt-get install "+holdpkg+" -y").c_str());
    
  }
  pkgin = 0;

}

void AppRem(list<string> remappList) 
{
    
    int pkgout = 0;
    pkgout += remappList.size();

    for (int j = 0; j < pkgout; j++) {
    
        string pacgOut = remappList.front();
        remappList.pop_front();

        system(("sudo apt-get --purge remove "+pacgOut+" -y").c_str());
    
  }
  pkgout = 0;
  
}
void ReadConfSsh(ifstream& confsshIn, Ssdhconstrct& ssdstrct)
{
  getline( confsshIn, ssdstrct.strctconfssh );
}
void ConfSshPrint(ofstream& confsshOut, Ssdhconstrct& ssdstrct)
{
  confsshOut << ssdstrct.strctconfssh << endl;
}
void ReadSsdh(ifstream& ssdHin, Ssdhconstrct& ssdstrct)
{
  getline( ssdHin, ssdstrct.strctssd );
}
void SsdhPrnt(ofstream& ssdHut, Ssdhconstrct& ssdstrct)
{
  ssdHut << ssdstrct.strctssd << endl;
}
void SsdRnRead(ifstream& bakRnSsd, Ssdhconstrct& ssdstrct)
{
  getline( bakRnSsd, ssdstrct.rnstrctssd );
}
void SsdRnPrnt(ofstream& ssdRn, Ssdhconstrct& ssdstrct)
{
  ssdRn << ssdstrct.rnstrctssd << endl;
}
void SileReadIn(ifstream& sctlIn, Confstruct& confstruct)
{
    getline( sctlIn, confstruct.silestrct );
}
void SileBakPrint(ofstream& sctlOut, Confstruct& confstruct)
{
    sctlOut << confstruct.silestrct << endl;
}
void ProfReadIn(ifstream& profIn, Confstruct& confstruct)
{
    getline( profIn, confstruct.prostrct );
}
void ProfBakPrint(ofstream& profOut, Confstruct& confstruct)
{
    profOut << confstruct.prostrct << endl;
}
void LimReadIn(ifstream& limIn, Confstruct& confstruct)
{
    getline( limIn, confstruct.limstrct );
}
void LimBakPrint(ofstream& limOut, Confstruct& confstruct)
{
    limOut << confstruct.limstrct << endl;
}
void ConfigureSsh(ofstream& ssdConf, list<string> ssdhList)
{
    string confHoldssd = "";

    int cntsshd = 0;

    cntsshd += ssdhList.size();

    for (int j = 0; j < cntsshd; j++) {

        confHoldssd = ssdhList.front();
        ssdhList.pop_front();
        ssdhList.clear();
        ssdConf << confHoldssd << endl;
        confHoldssd = "";
    }
    cntsshd = 0;

}
void SsdhConfigure(ifstream& ssdIn, ofstream& ssdOut)
{

    string thetmp = "";
    string linessd;

    int index;
    int cntln = 0;

    while ( getline( ssdIn, linessd ) ) {

        if ( cntln == 27 ) {

            ssdOut << "PermitRootLogin no" << endl;

            linessd = "";

        }
        else if ( cntln == 63 ) {

            ssdOut << "X11Forwarding no" << endl;

            linessd = "";

        }

        else {

            index = linessd.find('\0');

            string ssdword = linessd.substr(0, index);

            thetmp = ssdword;

            ssdOut << thetmp << endl;

            thetmp = "";

        }

        cntln++;

    }

    cntln = 0;

}
void SsdRnScrip(ifstream& scrpRn, ofstream& rnScrp)
{

    string rnssd;
    string wordSsd = "";
    int ssrndex;
    int rnct = 0;

    while ( getline( scrpRn, rnssd ) ) {

        if ( rnct == 70 ) {

            rnScrp << "        chmod 0000 /var/run/sshd" << endl;

            rnssd = "";

        }
        else {

            ssrndex = rnssd.find('\0');

            string thessdHold = rnssd.substr(0, ssrndex);
            wordSsd = thessdHold;

            rnScrp << wordSsd << endl;
            wordSsd = "";

        }

        rnct++;

    }

    rnct = 0;
}
void SctlPrintOut(ifstream& inSctl, ofstream& outSctl, list<string> sctlconList)
{

    string silelin;

    int silex;
    string wordPro = "";

    string holdOne = "";
    int cntsctl = 0;

    cntsctl += sctlconList.size();
    int sctlcnt = 0;

    while ( getline( inSctl, silelin ) ) {

        if ( sctlcnt == 59 ) {

            for (int j = 0; j < cntsctl; j++) {

                wordPro = sctlconList.front();
                sctlconList.pop_front();

                outSctl << wordPro << endl;
                wordPro = "";

            }

            silelin = "";

        }
        else {

            silex = silelin.find('\0');
            string theSileHold = silelin.substr(0, silex);

            wordPro = theSileHold;

            outSctl << wordPro << endl;
            wordPro = "";

        }

        sctlcnt++;

    }

    cntsctl = 0;
    sctlcnt = 0;

}
void ProfPrintOut(ifstream& inProf, ofstream& outProf, list<string> proList)
{

    string prolin;
    int prodex;

    string wordPro = "";
    string holdOne = "";

    int prfcnt = 0;
    int cntprf = 0;

    cntprf += proList.size();

    for (int i = 0; i < cntprf; i++) {

        wordPro = proList.front();
        proList.pop_front();

        outProf << wordPro << endl;
        wordPro = "";

    }
    while ( getline( inProf, prolin ) ) {

        if ( prfcnt >= 2 ) {

            prodex = prolin.find('\0');
            string theProHold = prolin.substr(0, prodex);

            wordPro = theProHold;
            outProf << wordPro << endl;
            wordPro = "";

        }
        else {

            prolin = "";

        }

        prfcnt++;

    }

    cntprf = 0;
    prfcnt = 0;

}
void LimPrintOut(ifstream& inLim, ofstream& outLim, list<string> limList)
{

    int limdex;
    string limconHold = "";
    int limcnt = 0;
    int cntlim = 0;

    cntlim += limList.size();

    string limline;

    while ( getline( inLim, limline ) ) {

        if ( limcnt == 54 ) {

            for (int i = 0; i < cntlim; i++) {

                limconHold = limList.front();
                limList.pop_front();

                outLim << limconHold << endl;
                limconHold = "";

            }

            limline = "";

        }
        else {

            limdex = limline.find('\0');

            string holdLimcon = limline.substr(0,limdex);
            limconHold = holdLimcon;

            outLim << limconHold << endl;
            limconHold = "";

        }

        limcnt++;

    }

    limcnt = 0;
    cntlim = 0;

}

