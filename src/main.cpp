#include "header.h"

bool arLinkas(const string x){
    const regex pattern("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    return regex_match(x, pattern);
}

bool neRaide(char x){
    if (isdigit(x) || isalpha(x)) {
        return false;
    }
    return true;
}

void skaityti (multimap<string, int> &zodziai, vector<string> &linkai, int &stulp){
    stulp = 1;

    ifstream file ("tekstas.txt");

    while (!file.eof()){
        string line;
        std::getline(file, line);
        std::stringstream eil(line);
        string zodis;
        while (eil >> zodis) {
            if (arLinkas(zodis)) {
                linkai.push_back(zodis);
            }
            else {
                zodis.erase(remove_if(zodis.begin(), zodis.end(), neRaide), zodis.end());
                if (!zodis.empty())
                    zodziai.insert({ zodis, stulp });
            }
        }
        stulp++;
    }
    file.close();
}

void spausdinti (multimap<string, int> zodziai) {
    ofstream fileof("rezultatas.txt");
    fileof<<setw(20)<<left<<"Zodis "<<setw(20)<<"Pasikartojimu kiekis"<<" "<<endl;
    for (auto it = zodziai.begin(), end = zodziai.end(); it != end; it = zodziai.upper_bound(it->first)) {
        if (zodziai.count(it->first) > 1) fileof<<setw(20)<<left<< it->first <<setw(20)<<right<<zodziai.count(it->first)<<endl;
    }
    fileof.close();
}

void spausdintiLentele (multimap<string, int> zodziai, int stulp){
    int j;
    int x = 1;
    ofstream fileof("lentele.txt");
    fileof<<setw(15)<<right<<"|";
    for(int i = 1; i < stulp; i++){
        fileof<<setw(5)<<right<<i<<" |";
    }
    fileof<<endl;
    for (auto it = zodziai.begin(), end = zodziai.end(); it != end; it = zodziai.upper_bound(it->first)){
        if(zodziai.count(it->first) > 1){
            fileof<<setw(14)<<right<<it->first<<"|";
            for (auto itline = zodziai.equal_range(it->first).first; itline != zodziai.equal_range(it->first).second; ++itline){
                int sk = itline->second;
                j = x;
                if(j>sk) continue;
                while (j!=sk && j!=stulp){
                    fileof<<setw(5)<<""<<" |";
                    j++;
                }
                fileof<<setw(5)<<right<<"X"<<" |";
                x = sk+1;
            }
            x = 1;
            fileof<<endl;
        }
    }
    fileof.close();
}

void spausdintiURL (vector<string> linkai) {
    if(linkai.size() < 1) cout<<"URL adresu tekste nera."<<endl;
    else {
        cout<<"Tekste rasti URL adresai: "<<endl;
        for (int i = 0; i < linkai.size(); i++)
        {
            cout<<linkai[i]<< endl;
        }
    }
}

int main () {
	multimap<string, int> zodziai;
	vector<string> linkai;
	string pav;
    int stulp;

    skaityti(zodziai,linkai,stulp);
    spausdinti(zodziai);
    spausdintiLentele(zodziai,stulp);
    spausdintiURL(linkai);
}
