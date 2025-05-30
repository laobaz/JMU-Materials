#pragma once
#include"init.h"

void input() {
    string input_str;
    while (getline(cin, input_str)) {
        if (!(input_str[0] >= 'A' && input_str[0] <= 'Z')) {
            break;
        }

        int i = 0;
        string tmp = "";
        while (input_str[i] != ':') {
            tmp += input_str[i++];
        }
        i += 3;//����::=
        production temp_pro(tmp);
        while (true) {
            tmp = "";
            while (input_str[i] != ' ') {
                tmp += input_str[i];
                i++;
                if (i >= input_str.length()) {
                    break;
                }
            }
            temp_pro.push(tmp);
            if (i < input_str.size()) {
                i++;
            }
            else {
                break;
            }
        }
        productions.push_back(temp_pro);
    }

}

//�����ķ�
void Augmented_grammar() {
    cout << "��ʼ���������ķ�" << endl;
    if (!productions.empty()) {
        G_start = "G'";
        production start_production(G_start);
        start_production.push(productions[0].left);
        productions.insert(productions.begin(), start_production);
        int i = 0;
        for (auto& pro : productions) {
            pro.index = i;
            i++;
        }
    }
}

void printProductions() {
    //����ʽ���
    int j = 1;
    for (int i = 0; i < productions.size(); i++) {
        productions[i].print();
        j++;
    }
}

void calVN() {

    for (auto it : productions) {
        if (nonterminal.count(it.left) < 1) {
            nonterminal.insert(it.left);
        }
        for (int i = 0; i < it.right.size(); i++) {
            if (it.right[i][0] >= 'A' && it.right[i][0] <= 'Z') {
                if (nonterminal.count(it.right[i]) < 1) {
                    nonterminal.insert(it.right[i]);
                }
            }
        }
    }
}

void calVT() {
    for (auto it : productions) {
        for (int i = 0; i < it.right.size(); i++) {
            if (nonterminal.count(it.right[i]) == 0 && Finalization.count(it.right[i]) == 0) {
                Finalization.insert(it.right[i]);
            }
        }
    }
    //��ӽ�����
    Finalization.insert("#");
}

void printVNT() {
    cout << "���ս����";
    for (auto it : nonterminal) {
        cout << it << " ";
    }
    cout << endl;
    cout << "�ս����";
    for (auto it : Finalization) {
        if (it != "#") {
            cout << it << " ";
        }
    }
    cout << endl;
}

void initFcollections() {
    for (auto it : nonterminal) {
        first_follow f(it);
        if (it == G_start) {
            //�ķ���ʼ�� #����FOLLOW��
            f.insert_follow("#");
        }
        fcollections.push_back(f);
    }
}

void calFIRST() {
    bool is_change = true;  // ���ÿ��ɨ��׼�Ƿ����FIRST����
    while (is_change)
    {
        is_change = false;
        for (int i = 0; i < productions.size(); i++)
        {
            int k = 0;
            //����fcollections[k].vn = productions[i].left ��Ϊ��ǰ�����ķ��ս��
            for (k = 0; k < fcollections.size(); k++)
            {
                if (fcollections[k].vn == productions[i].left)
                {
                    break;
                }
            }

            bool have_e = false;    //����ܷ�һֱ�Ƴ���
            for (int ri = 0; ri < productions[i].right.size(); ri++) {
                // �����ú�ѡʽ���Ҳ�
                have_e = false;
                //�Ƿ��ս��  E->A���� FIRST[E] += ( FIRST[A] - {��} );
                if (productions[i].right[ri][0] >= 'A' && productions[i].right[ri][0] <= 'Z') 
                {
                    //��fcollections[h].vn = productions[i].right[ri] ���Ҳ�Ҫ�����ķ��ս�� A
                    int h = 0;
                    for (; h < fcollections.size(); h++) {
                        if (fcollections[h].vn == productions[i].right[ri]) {
                            break;
                        }
                    }

                    //�ж�FIRST[A]�ǿ�
                    if (!(fcollections[h].vfirst.empty())) {
                        //�ж�FIRST[A]���Ƿ������FIRST[E]����Ԫ��
                        for (auto it : fcollections[h].vfirst) {
                            if (it != "��") {
                                //����FIRST[E]����
                                if (fcollections[k].vfirst.count(it) < 1) {
                                    is_change = true;
                                }
                                fcollections[k].insert_first(it);
                            }
                        }
                    }
                    else {
                        //FIRST[A]Ϊ��
                        //��������
                        break;
                    }

                    if (fcollections[h].vfirst.count("��")) {
                        //�� ���� FIRST[A] ���������Ҳ�
                        have_e = true;
                    }
                    else {
                        // ��������ѭ��
                        break;
                    }
                }
                //���ս�� �� ��
                else {
                    // E->a���� FIRST[E] += {a};
                    if (fcollections[k].vfirst.count(productions[i].right[ri]) < 1) {
                        is_change = true;
                    }
                    fcollections[k].insert_first(productions[i].right[ri]);   //����FIRST����
                    //�ս�� ����ѭ��
                    break;
                }
            }
            if (have_e) {
                //��һֱ�Ƴ���
                // FIRST[E] += {��}
                fcollections[k].insert_first("��");
            }

        }

    }

}

void calFOLLOW() {
    bool is_change = true;  // ���ÿ��ɨ�����Ƿ����FOLLOW����
    while (is_change) {
        is_change = false;
        for (int i = 0; i < productions.size(); i++)
        {
            for (int j = 0; j < productions[i].right.size(); j++) {
                //�ж��Ƿ�Ϊ���ս��
                if (productions[i].right[j][0] >= 'A' && productions[i].right[j][0] <= 'Z')
                {
                    //1.��ʽΪ A->aF  follow(A)���뵽follow(F)
                    if (j + 1 == productions[i].right.size()) {

                        int k = 0, m = 0, fg = 0;
                        //����fcollections[k].vn=A 
                        //   fcollections[m].vn=F
                        for (int nn = 0; nn < fcollections.size(); nn++)
                        {
                            if (fcollections[nn].vn == productions[i].left)
                            {
                                k = nn;
                                fg++;
                            }
                            if (fcollections[nn].vn == productions[i].right[j])
                            {
                                m = nn;
                                fg++;
                            }
                            if (fg == 2) {
                                break;
                            }
                        }

                        //�ж�FOLLOW[A]�Ƿ�Ϊ��
                        if (!(fcollections[k].vfollow.empty())) {
                            //�ж�FOLLOW[A]���Ƿ�����Ԫ��
                            for (auto it : fcollections[k].vfollow) {
                                if (fcollections[m].vfollow.count(it) < 1) {
                                    fcollections[m].insert_follow(it);    //����FOLLOW����
                                    is_change = true;
                                }
                            }
                        }
                    }

                    //2.��ʽΪ A->aFB FIRST(B)-�� ���뵽follow(F)
                    else if (productions[i].right[j + 1][0] >= 'A' && productions[i].right[j + 1][0] <= 'Z')
                    {
                        int k = 0, m = 0, fg = 0;
                        //����fcollections[k].vn=F 
                        //   fcollections[m].vn=B
                        for (int nn = 0; nn < fcollections.size(); nn++)
                        {
                            if (fcollections[nn].vn == productions[i].right[j])
                            {
                                k = nn;
                                fg++;
                            }
                            if (fcollections[nn].vn == productions[i].right[j + 1])
                            {
                                m = nn;
                                fg++;
                            }
                            if (fg == 2) {
                                break;
                            }
                        }

                        int flag_e = 0;
                        for (auto it : fcollections[m].vfirst) {
                            if (it == "��") {
                                flag_e = 1;
                            }
                            if (it != "��")   //��ȥ��
                            {
                                if (fcollections[k].vfollow.count(it) < 1) {
                                    fcollections[k].insert_follow(it);    //����FOLLOW����
                                    is_change = true;
                                }
                            }
                        }

                        // 2.2 B->...->�� follow(A)���뵽follow(F)
                        if (flag_e) {
                            // fcollections[k].vn=F 
                            // ����fcollections[m].vn=A
                            for (m = 0; m < fcollections.size(); m++)
                            {
                                if (fcollections[m].vn == productions[i].left)
                                {
                                    break;
                                }
                            }
                            //�ж�FOLLOW[A]�Ƿ�Ϊ��
                            if (!(fcollections[m].vfollow.empty()))
                            {
                                //�ж�FOLLOW[A]���Ƿ�����Ԫ��
                                for (auto it : fcollections[m].vfollow)
                                {
                                    if (fcollections[k].vfollow.count(it) < 1)
                                    {
                                        fcollections[k].insert_follow(it);    //����FOLLOW����
                                        is_change = true;
                                    }
                                }
                            }
                        }




                    }

                    //3.��ʽΪ A->aFb {b}���뵽follow(F)
                    else
                    {
                        int k = 0;
                        //����fcollections[k].vn=F
                        for (k = 0; k < fcollections.size(); k++)
                        {
                            if (fcollections[k].vn == productions[i].right[j])
                            {
                                break;
                            }
                        }
                        //�ж��Ƿ�Ҫ����follow����
                        if (fcollections[k].vfollow.count(productions[i].right[j + 1]) < 1) {
                            fcollections[k].insert_follow(productions[i].right[j + 1]);    //����FOLLOW����
                            is_change = true;
                        }
                    }

                }
            }
        }
    }
}


void printFirstFollow() {
    for (int i = 0; i < fcollections.size(); i++) {
        fcollections[i].print();
    }
}


bool isVN(string str) {
    return (nonterminal.count(str) > 0);
}

string getpro(int j) {
    string res = "";
    res += productions[j].left;
    res += "->";
    for (auto it : productions[j].right) {
        res += it;
        res += " ";
    }
    return res;
}



void inputIstr() {
    cout << "��������������ִ�(��#��β)�� ";
    cin >> wait_ananly;
    wait_ananly = wait_ananly + "#";
    cout << "��ʼ��������" << endl;
}

string getStackStr(const stack<string>& G_F) {

    stack<string> s;//����ջ
    vector<string> str;
    string res = "";
    s = G_F;
    while (!s.empty()) {
        str.push_back(s.top());
        s.pop();
    }
    for (int i = str.size() - 1; i >= 0; i--) {
        res += (str[i]+" ");
    }
    return res;
}


//�ƽ���Ŀ        // �ƽ���Ŀ
//��Լ��Ŀ        // ��Լ��Ŀ
//��Լ��Ŀ    // ��Լ��Ŀ
//������Ŀ     // ������Ŀ
//��ʼ����Ŀ������Ŀ���淶��׼��
void Initialize_Project() {
    int num = 0;
    for (auto obj : productions) {
        //if ����ʽΪA->��,ֻ������A->��
        if (obj.right.at(0).compare("��") == 0) {
            Project pro(obj.index, num);
            num++;
            pro.type = "��Լ��Ŀ";
            pro.rightstr = "��";
            continue;
        }
        //��Ϊ�ռ���������ʼ��
        for (int i = 0; i <= obj.right.size(); i++) {
            Project pro(obj.index, num);
            pro.index_point = i;
            //ΪG->E&&G->E��
            if (obj.index == 0 && i == obj.right.size()) {
                pro.type = "������Ŀ";
            }
            //ΪE->T��
            else if (obj.right.size() == i) {
                pro.type = "��Լ��Ŀ";
            }
            //ΪE->��T
            else if (isVN(obj.right.at(i))) {
                pro.type = "��Լ��Ŀ";
            }
            //ΪE->��+T
            else {
                pro.type = "�ƽ���Ŀ";
            }
            pro.leftstr = obj.left;
            if (i == obj.right.size()) {
                pro.rightstr = "none";
            }
            else {
                pro.rightstr = obj.right.at(i);
            }
            projects.push_back(pro);
            num++;
        }
    }
}

Project& find_projects(int num) {
    for (int i = 0; i < projects.size(); i++) {
        if (projects.at(i).number == num)
            return projects.at(i);
    }
    Project pro;
    return pro;

}
int find_next_projects(int num) {
    //Ѱ�ҵ�ǰ��Ŀ��ŵ���һ����Ŀ
    int next_pro = -1;
    Project pro = find_projects(num);
    //�����Ŀ����Ϊ ��Լ��Ŀ or �ƽ���Ŀ ��ʾ����һ��
    if (pro.type == "��Լ��Ŀ" || pro.type == "�ƽ���Ŀ") {
        for (auto obj : projects) {
            //�������ͬһ������ʽ&&�ǵ�ǰ��Ŀ����һ������
            if (pro.index == obj.index && obj.index_point == pro.index_point + 1) {
                return obj.number;
            }
        }
    }
    else {
        cout << "���ִ���" << endl;
        return next_pro;
    }
}
void Project_Set_Specification_Family() {
    //��I0
    Family pro_family(0);
    //��¼���ķ��ս��
    vector<string> left;
    left.push_back(projects.at(0).leftstr);
    //��¼�Ҳ���һλ�ķ��ս��
    vector<string> right;
    right.push_back(projects.at(0).rightstr);
    //G'->E�ȼ��뵽I0�У�
    pro_family.project_num.push_back(projects.at(0).number);
    //�ж��Ƿ񶼰���
    bool pro_family_all = true;
    do {
        //Ĭ��Ϊ���һ��
        pro_family_all = true;
        //�ҷ��ս���Ķ�Ӧ����Ŀ
        for (auto obj : right) {
            //��������Ŀ����δ���ֹ�
            if (find(left.begin(), left.end(), obj) == left.end()) {
                for (auto obj1 : projects) {
                    //����δ���ս��
                    if (obj1.leftstr == obj && obj1.index_point == 0) {
                        pro_family.project_num.push_back(obj1.number);
                        pro_family_all = false;
                        //�����Ҳ�
                        if (find(right.begin(), right.end(), obj1.rightstr) == right.end() && (isVN(obj1.rightstr))) {
                            right.push_back(obj1.rightstr);
                        }

                    }
                }
                //���뵽�����ս��
                left.push_back(obj);
                break;
            }
        }
    } while (!pro_family_all);
    //I0�������
    Family_table.push_back(pro_family);
    bool is_add_family = true;
    //��¼������һ��������
    vector<string>right_input;
    //��ǰ��family
    int fa_ID = 0;
    do
    {
        is_add_family = true;
        right_input.clear();
        for (auto i : Family_table[fa_ID].project_num) {
            Project temp = find_projects(i);
            //��ǰ��ĿΪ������Ŀ���߽�����Ŀʱ
            if (temp.type == "��Լ��Ŀ" || temp.type == "������Ŀ")
                continue;
            if (find(right_input.begin(), right_input.end(), temp.rightstr) == right_input.end()) {
                right_input.push_back(temp.rightstr);
            }
        }
        //���α����Ҳ������
        for (string obj : right_input) {
            //�����ڶ�ȡ��һ���ַ�����
            int i = Family_table.size();
            Family new_Family(i);
            //�鿴��ǰ���еĶ�ȡ�����һ����
            for (int obj1 : Family_table[fa_ID].project_num) {
                Project temp = find_projects(obj1);
                if (temp.rightstr == obj) {
                    int next_pro = find_next_projects(temp.number);
                    if (next_pro == -1) {

                    }
                    else {
                        new_Family.project_num.push_back(next_pro);
                    }
                }
            }
            // ÿ��ѭ��ֱ��CLOSURE(I)��������Ϊֹ
            int cur = 0;
            //���� S->.A S->a A->.S  �����S����Ŀ��ѭ������
            set<string> left_;
            for (int i : new_Family.project_num) {
                Project temp = find_projects(i);
                //ʹ��Ϊͷ
                if (temp.index_point == 0) {
                    right_input.push_back(temp.leftstr);
                }
            }
            //����µ�Family�еĺ����Ŀ
            pro_family_all = true;
            do
            {
                pro_family_all = true;
                //�µ��Ҳ������
                vector<string> new_right;
                int new_Family_size = new_Family.project_num.size();
                for (int j = cur; j < new_Family_size; j++) {
                    Project temp = find_projects(new_Family.project_num.at(j));
                    //�Ҳ�Ϊ���ս��
                    if (isVN(temp.rightstr)) {
                        //E->.E�����
                        if (temp.leftstr == temp.rightstr && temp.index == 0) {
                            continue;
                        }
                        else if (left_.count(temp.rightstr) > 0) {
                            continue;
                        }
                        //����
                        else {
                            left_.insert(temp.rightstr);
                        }
                        //��ӽ�ȥ
                        new_right.push_back(temp.rightstr);
                    }
                }
                for (string obj1 : new_right) {
                    //�ҵ�E->S.A �е�A����Ŀ
                    for (auto obj2 : projects) {
                        if (obj1 == obj2.leftstr && obj2.index_point == 0) {
                            new_Family.project_num.push_back(obj2.number);
                            //���ܶ�ȡ�Ļ������µ�
                            pro_family_all = false;
                        }
                    }
                }
                cur = new_Family_size;
                new_right.clear();
            } while (!pro_family_all);

            //�ж��½���״̬�Ƿ���Ѿ�������״̬�غ�
            bool flag_tmp = false;
            for (auto obj3 : Family_table) {
                //���ﲻ��Ҫ����������Ӧ�ô�СҲ��ͬ
                //&&new_Family.project_num.size()==obj3.project_num.size()
                if (new_Family == obj3 && new_Family.project_num.size() == obj3.project_num.size()) {
                    flag_tmp = true;
                    Goto go(obj, fa_ID, obj3.family_num);
                    gototables.push_back(go);
                    break;
                }
            }
            if (!flag_tmp) {
                //û���ظ���
                Family_table.push_back(new_Family);
                Goto go(obj, fa_ID, new_Family.family_num);
                gototables.push_back(go);
                is_add_family = false;

            }
        }
        //��һ��
        fa_ID++;
        if (fa_ID >= Family_table.size())
            break;
        else
            is_add_family = false;


    } while (!is_add_family);
}
void ActionTable() {
    //��Ŀ��
    for (auto obj : Family_table) {
        //��Ŀ���е���Ŀ
        for (int obj1 : obj.project_num) {
            Project temp = find_projects(obj1);
            //��Ϊ�ƽ���Ŀ�����Ҳ�Ϊ�ս��ʱ
            if (temp.type == "�ƽ���Ŀ" && (!isVN(temp.rightstr))) {
                int goto_family = 0;
                for (auto obj2 : gototables) {
                    if (obj2.nonterminal == temp.rightstr &&
                        obj2.state == obj.family_num)
                    {
                        break;
                    }
                    goto_family++;
                }
                string action = "S" + to_string(gototables.at(goto_family).FN);
                //�ս�� ���� <goto>
                Action act(temp.rightstr, obj.family_num, action);
                Actiontables.push_back(act);
            }
            //G'->E. ������Ŀ������Ik, Action[k, #] = acc
            else if (temp.type == "������Ŀ") {
                Action act("#", obj.family_num, "acc");
                Actiontables.push_back(act);
            }
            //��Լ��Ŀ for all a �� FOLLOW(A), do Action[k, a] = rj (j�ǲ���ʽA->a�ı��)
            else if (temp.type == "��Լ��Ŀ") {
                int follow = 0;
                for (auto obj2 : fcollections) {
                    //���follow���еķ��ս����Ӧ����ǰ��Ŀ���ս��
                    if (obj2.vn == temp.leftstr) {
                        break;
                    }
                    follow++;
                }
                for (auto obj2 : fcollections.at(follow).vfollow) {
                    string action = "r" + to_string(temp.index);
                    Action act(obj2, obj.family_num, action);
                    Actiontables.push_back(act);
                }
            }
        }
    }
}

string judege_conflict(const Family& Fa) {
    int move = 0;
    int reduce = 0;
    for (auto obj : Fa.project_num) {
        //��ȡ��ǰ��Ŀ���е�������Ŀ
        Project temp = find_projects(obj);
        if (temp.type == "��Լ��Ŀ") {
            reduce++;
        }
        else if (temp.type == "�ƽ���Ŀ")
        {
            move++;
        }
    }
    //�������ƽ��͹�Լʱ
    if (move > 0 && reduce > 0)
    {
        //�ƽ�-��Լ��ͻ
        return "MRCONFLICT";
    }
    //���ߴ��ڶ��������ϵĹ�Լ
    else if (reduce >= 2) {
        //��Լ-��Լ��ͻ
        return "RRCONFLICT";
    }
    else {
        //�޳�ͻ
        return "NONECONFLICT";
    }
}

bool judgeG() {

    bool judgeG = true;
    vector<string>move;//����ƽ����ս��
    vector<string>reduce;//��Ź�Լ�ķ��ս��
    for (auto obj : Family_table) {
        //�鿴ʲô��ͻ
        string conflict = judege_conflict(obj);
        if (conflict == "MRCONFLICT") {
            //��������ƽ�-��Լ��ͻ
            //A->B. A->B.*
            //{*} �� follow(A)��=�ռ�
            cout << obj.family_num << "�д����ƽ�-��Լ��ͻ\t" ;
            move.clear();
            reduce.clear();
            for (auto obj1 : obj.project_num) {
                Project temp = find_projects(obj1);
                if (temp.type == "�ƽ���Ŀ") {
                    move.push_back(temp.rightstr);
                }
                else if (temp.type == "��Լ��Ŀ")
                    reduce.push_back(temp.leftstr);
            }
            string fb;
            for (auto obj1 : reduce) {
                first_follow temp(obj1);
                vector<first_follow>::iterator ff = find(fcollections.begin(), fcollections.end(), temp);
                //�����ս��
               
                for (auto obj2 : move) {
                    fb = obj2;
                    if (find((*ff).vfollow.begin(), (*ff).vfollow.end(), obj2) != (*ff).vfollow.end()) {

                        judgeG = false;
                        break;
                    }
                   
                }
                if (judgeG == false) 
                {
                    cout <<"�ս����"<<obj1 << "��Follow���ͷ��ս����" << fb << "��first��" << "�Ľ�����Ϊ�ն���"<<fb << endl;
                    break;
                }
                else
                {
                    cout << "�ս����" << obj1 << "��Follow���ͷ��ս����" << fb << "��first��" << "�Ľ���Ϊ��" << endl;
                }
            }

        }
        else if (conflict == "RRCONFLICT") {
            //A->B.  C->D.
            //follow(A) �� follow(C)��=�ռ�
            cout << obj.family_num << "�д��ڹ�Լ-��Լ��ͻ" << endl;
            reduce.clear();
            for (auto obj1 : obj.project_num) {
                Project temp = find_projects(obj1);
                if (temp.type == "��Լ��Ŀ")
                    //������
                    reduce.push_back(temp.leftstr);
            }
            for (auto obj1 : reduce)
            {
                int i = 0;
                first_follow temp(obj1);
                vector<first_follow>::iterator fA = find(fcollections.begin(), fcollections.end(), temp);
                //sort((*fA).vfollow.begin(), (*fA).vfollow.end());
                string fb;
                for (int j = i + 1; j < reduce.size(); j++) {
                    first_follow temp(reduce.at(j));
                    vector<first_follow>::iterator fB = find(fcollections.begin(), fcollections.end(), temp);
                    //sort((*fB).vfollow.begin(), (*fB).vfollow.end());
                    //�󽻼�
                    vector<string> target;
                    target.resize(min((*fB).vfollow.size(), (*fA).vfollow.size()));
                    vector<string>::iterator itend = set_intersection(
                        (*fB).vfollow.begin(), (*fB).vfollow.end(),
                        (*fA).vfollow.begin(), (*fA).vfollow.end(),
                        target.begin());
                    //˵���н���
                    if (target.begin() != target.end())
                    {
                        judgeG = false;
                        fb = reduce.at(j);
                        break;
                    }
                }
                if (judgeG == false)
                {
                    cout <<"�ս����" << obj1 << "��Follow�����ս����" << fb << "��Follow��" << "�Ľ�����Ϊ��" << endl;
                    break;
                }
                else {
                    cout <<"�ս����" << obj1 << "��Follow�����ս����" << fb << "��Follow��" << "�Ľ���Ϊ�ռ�" << endl;
                }
            }
        }
        if (judgeG == false) {
            cout << "����SLR�ķ�" << endl;
            break;
        }

    }
    if (judgeG) {
        cout << "��SLR�ķ�" << endl;

    }
    return judgeG;
}


void analysis_SLR() {
    inputIstr();
    //ѹ����ֹ���ź��ķ��Ŀ�ʼ����
    GAnalasis.push("#");
    Family_stack.push("I0");
    int i = 0, steps = 0;
    cout << wait_ananly << " �ķ����������£�" << endl;
    cout << setw(16) << left << "���̼���";
    cout << setw(20) << left << "�﷨����ջ";
    cout << setw(20) << left << "״̬����ջ";
    cout << setw(20) << left << "ʣ��δƥ����ִ�";
    cout << setw(20) << left << "����";
    cout << endl;
    for (int p = 0; p < 12; p++)
        cout << "�������� ";
    cout << endl;
    while (i < wait_ananly.length()) {
        steps++;
        cout << setw(16) << left << steps;
        string tmp = getStackStr(GAnalasis);
        cout << setw(20) << left << tmp;
        tmp = getStackStr(Family_stack);
        cout << setw(20) << left << tmp;
        string tmp2 = "";
        for (int j = i; j < wait_ananly.length(); j++) {
            tmp2 += wait_ananly[j];
        }
        cout << setw(20) << left << tmp2 ;

        char cur_c = wait_ananly[i];   //��ǰָʾ�ַ�
        //ȡջ��Ԫ��
        if (GAnalasis.empty()) {
            cout << "ջΪ�գ�����" << endl;
            return;
        }

        bool is_id = false;
        int add_i = 0;
        string str;
        //�����id
        if ((Finalization.count("id") > 0) && (cur_c >= 'a' && cur_c <= 'z') || (cur_c >= '0' && cur_c <= '9')) {
            //ƥ��ɹ�
            str += cur_c;
            add_i ++;
            is_id = true;
            do {
                if ((wait_ananly[i + add_i] >= 'a' && wait_ananly[i + add_i] <= 'z') ||
                    (wait_ananly[i + add_i] >= '0' && wait_ananly[i + add_i] <= '9'))
                {
                    str += wait_ananly[i + add_i];
                    //is_id = true;
                }
                else
                {
                    break;
                }
                add_i++;
            } while ((add_i + i) < wait_ananly.size());
        }
        //ȡ��Ŀ����
        if (!is_id) {
            str = cur_c;
            add_i++;
        }

        int topFamily = stoi(Family_stack.top().substr(1).c_str());
        bool is_error = true;
        Action act;
        for (auto obj : Actiontables) {
            if (topFamily == obj.state) {
                if (is_id && obj.Finalization == "id") {
                    act = obj;
                    is_error = false;
                    break;
                }
                if (obj.Finalization ==str) {
                    act = obj;
                    is_error = false;
                    break;
                }
            }

        }
        if (is_error) {
            cout << "error!!!" << endl;
            return;
        }
        if (act.F2S[0] == 'S') {
            //�ƽ�����
            i+=add_i;

            cout << setw(20) << left << "�ƽ�"<<endl;
            int next_state = stoi(act.F2S.substr(1));
            //״̬ѹջ
            string next_I = "I" + to_string(next_state);
            Family_stack.push(next_I);
            //�﷨ѹջ

            GAnalasis.push(str);
        }
        else if (act.F2S[0] == 'r') {
            //��Լ
            int next_Reduce = stoi(act.F2S.substr(1));
            production pro;
            for (auto obj : productions) {
                if (next_Reduce == obj.index) {
                    pro = obj;
                    break;
                }
            }
            string prostr = "��Լ:" + pro.left + "->";
            for (auto obj : pro.right) {
                prostr += obj;
            }
            cout << setw(20) << left << prostr << endl;
            //���й�Լ���� ��F->id  ��Լ��F������ջ��
            for (auto obj : pro.right) {
                GAnalasis.pop();
                Family_stack.pop();
            }
            int top_FS = stoi(Family_stack.top().substr(1).c_str());
            GAnalasis.push(pro.left);
            for (auto obj1 : gototables) {
                if (pro.left == obj1.nonterminal && obj1.state == top_FS) {
                    //�µ�״̬ѹջ
                    string next_I = "I" + to_string(obj1.FN);
                    Family_stack.push(next_I);
                    break;
                }
            }
        }
        else if (act.F2S == "acc") {
            //acc ����
            cout << setw(20) << left << "����";
            cout << endl;
            for (int p = 0; p < 12; p++)
                cout << "�������� ";
            cout << endl;
            return;
        }
    }
}
production find_production(int index) {
    for (auto obj : productions) {
        if (obj.index == index) {
            return obj;
        }
    }
}
void print_production(int i, const production& prod) {
    cout << prod.left << "->";
    for (int j = 0; j < prod.right.size(); j++)
    {
        if (j == i)
        {
            cout << "�� ";
        }
        cout << prod.right[j] << " ";
    }
    if (i == prod.right.size())
    {
        cout << "��";
    }
    cout << endl;
}
void print_family_table() {
    cout << "�淶��Ϊ" << endl;
    for (auto obj : Family_table) {
        cout << "\t  I-" << obj.family_num << endl;
        cout << "���\t����\t   ���ʽ" << endl;
        for (auto obj1 : obj.project_num) {
            Project pro = find_projects(obj1);
            production  prod = find_production(pro.index);
            cout << pro.number << "\t" << pro.type << "\t";
            print_production(pro.index_point, prod);
        }
    }
}
void Project::print() {
    production  prod = find_production(index);
    cout << number << "\t    " << type << "\t";
    print_production(index_point, prod);

}
void print_Project() {
    cout << endl;
    cout << "\t��Ŀ��" << endl;
    cout << "��Ŀ���\t����\t   ���ʽ" << endl;
    for (auto obj : projects) {
        obj.print();
    }
}

void printGototable() {
    cout << endl;
    cout << "\t\tGOTOtable" << endl;
    for (auto obj : gototables) {
        cout << "\t[ I" << obj.state << " , " << obj.nonterminal << "] ����> I" << obj.FN << endl;
    }
}

void printActiontables() {
    cout << endl;
    cout << "\t Actiontables" << endl;
    cout << "state  ";
    for (int i = 0; i < Finalization.size() / 2; i++) {
        cout << "   ";
    }
    cout << "action";
    for (int i = 0; i < nonterminal.size() / 2; i++) {
        cout << "   ";
    }
    cout << "GOTO";
    cout << endl;
    cout << "       ";
    for (string obj : Finalization) {
        cout << obj << "  ";
    }
    for (string obj : nonterminal) {
        if (obj != G_start) {
            cout << obj << "  ";
        }
    }
    cout <<endl;
    bool temp = false;
    for (auto obj : Family_table) {
        cout << "I" << obj.family_num << "    ";
        //ɨ��action 
        for (auto obj1 : Finalization) {
            temp = false;
            for (auto obj2 : Actiontables) {
                if (obj1 == obj2.Finalization && obj2.state == obj.family_num) {
                    cout << obj2.F2S << " ";
                    temp = true;
                    break;
                }

            }
            if (!temp) {
                cout << "   ";
            }
        }
        //ɨ��GOto
        for (auto obj1 : nonterminal) {
            temp = false;
            if (obj1 != G_start) {
                for (auto obj2 : gototables) {
                    if (obj2.state == obj.family_num && obj2.nonterminal == obj1) {
                        temp = true;
                        cout << "I" << obj2.FN << " ";
                        break;
                    }
                }

                if (!temp) {
                    cout << "   ";
                }
            }

        }
        cout << endl;

    }



}



