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
        i += 3;//跳过::=
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

//增广文法
void Augmented_grammar() {
    cout << "开始构造增广文法" << endl;
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
    //产生式编号
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
    //添加结束符
    Finalization.insert("#");
}

void printVNT() {
    cout << "非终结符：";
    for (auto it : nonterminal) {
        cout << it << " ";
    }
    cout << endl;
    cout << "终结符：";
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
            //文法开始符 #插入FOLLOW集
            f.insert_follow("#");
        }
        fcollections.push_back(f);
    }
}

void calFIRST() {
    bool is_change = true;  // 标记每轮扫瞄准是否更新FIRST集合
    while (is_change)
    {
        is_change = false;
        for (int i = 0; i < productions.size(); i++)
        {
            int k = 0;
            //定出fcollections[k].vn = productions[i].left 即为当前分析的非终结符
            for (k = 0; k < fcollections.size(); k++)
            {
                if (fcollections[k].vn == productions[i].left)
                {
                    break;
                }
            }

            bool have_e = false;    //标记能否一直推出ε
            for (int ri = 0; ri < productions[i].right.size(); ri++) {
                // 遍历该候选式的右部
                have_e = false;
                //是非终结符  E->A类型 FIRST[E] += ( FIRST[A] - {ε} );
                if (productions[i].right[ri][0] >= 'A' && productions[i].right[ri][0] <= 'Z') 
                {
                    //定fcollections[h].vn = productions[i].right[ri] 即右部要分析的非终结符 A
                    int h = 0;
                    for (; h < fcollections.size(); h++) {
                        if (fcollections[h].vn == productions[i].right[ri]) {
                            break;
                        }
                    }

                    //判断FIRST[A]非空
                    if (!(fcollections[h].vfirst.empty())) {
                        //判断FIRST[A]中是否有相对FIRST[E]的新元素
                        for (auto it : fcollections[h].vfirst) {
                            if (it != "ε") {
                                //更新FIRST[E]集合
                                if (fcollections[k].vfirst.count(it) < 1) {
                                    is_change = true;
                                }
                                fcollections[k].insert_first(it);
                            }
                        }
                    }
                    else {
                        //FIRST[A]为空
                        //跳过本轮
                        break;
                    }

                    if (fcollections[h].vfirst.count("ε")) {
                        //ε 属于 FIRST[A] 继续遍历右部
                        have_e = true;
                    }
                    else {
                        // 否则，跳出循环
                        break;
                    }
                }
                //是终结符 或 ε
                else {
                    // E->a类型 FIRST[E] += {a};
                    if (fcollections[k].vfirst.count(productions[i].right[ri]) < 1) {
                        is_change = true;
                    }
                    fcollections[k].insert_first(productions[i].right[ri]);   //更新FIRST集合
                    //终结符 跳出循环
                    break;
                }
            }
            if (have_e) {
                //能一直推出ε
                // FIRST[E] += {ε}
                fcollections[k].insert_first("ε");
            }

        }

    }

}

void calFOLLOW() {
    bool is_change = true;  // 标记每轮扫瞄中是否更新FOLLOW集合
    while (is_change) {
        is_change = false;
        for (int i = 0; i < productions.size(); i++)
        {
            for (int j = 0; j < productions[i].right.size(); j++) {
                //判断是否为非终结符
                if (productions[i].right[j][0] >= 'A' && productions[i].right[j][0] <= 'Z')
                {
                    //1.形式为 A->aF  follow(A)加入到follow(F)
                    if (j + 1 == productions[i].right.size()) {

                        int k = 0, m = 0, fg = 0;
                        //定出fcollections[k].vn=A 
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

                        //判断FOLLOW[A]是否为空
                        if (!(fcollections[k].vfollow.empty())) {
                            //判断FOLLOW[A]中是否有新元素
                            for (auto it : fcollections[k].vfollow) {
                                if (fcollections[m].vfollow.count(it) < 1) {
                                    fcollections[m].insert_follow(it);    //更新FOLLOW集合
                                    is_change = true;
                                }
                            }
                        }
                    }

                    //2.形式为 A->aFB FIRST(B)-ε 加入到follow(F)
                    else if (productions[i].right[j + 1][0] >= 'A' && productions[i].right[j + 1][0] <= 'Z')
                    {
                        int k = 0, m = 0, fg = 0;
                        //定出fcollections[k].vn=F 
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
                            if (it == "ε") {
                                flag_e = 1;
                            }
                            if (it != "ε")   //除去ε
                            {
                                if (fcollections[k].vfollow.count(it) < 1) {
                                    fcollections[k].insert_follow(it);    //更新FOLLOW集合
                                    is_change = true;
                                }
                            }
                        }

                        // 2.2 B->...->ε follow(A)加入到follow(F)
                        if (flag_e) {
                            // fcollections[k].vn=F 
                            // 定出fcollections[m].vn=A
                            for (m = 0; m < fcollections.size(); m++)
                            {
                                if (fcollections[m].vn == productions[i].left)
                                {
                                    break;
                                }
                            }
                            //判断FOLLOW[A]是否为空
                            if (!(fcollections[m].vfollow.empty()))
                            {
                                //判断FOLLOW[A]中是否有新元素
                                for (auto it : fcollections[m].vfollow)
                                {
                                    if (fcollections[k].vfollow.count(it) < 1)
                                    {
                                        fcollections[k].insert_follow(it);    //更新FOLLOW集合
                                        is_change = true;
                                    }
                                }
                            }
                        }




                    }

                    //3.形式为 A->aFb {b}加入到follow(F)
                    else
                    {
                        int k = 0;
                        //定出fcollections[k].vn=F
                        for (k = 0; k < fcollections.size(); k++)
                        {
                            if (fcollections[k].vn == productions[i].right[j])
                            {
                                break;
                            }
                        }
                        //判断是否要更新follow集合
                        if (fcollections[k].vfollow.count(productions[i].right[j + 1]) < 1) {
                            fcollections[k].insert_follow(productions[i].right[j + 1]);    //更新FOLLOW集合
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
    cout << "请输入待分析的字串(以#结尾)： ";
    cin >> wait_ananly;
    wait_ananly = wait_ananly + "#";
    cout << "开始分析……" << endl;
}

string getStackStr(const stack<string>& G_F) {

    stack<string> s;//分析栈
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


//移进项目        // 移进项目
//归约项目        // 归约项目
//待约项目    // 待约项目
//接受项目     // 接受项目
//初始化项目集，项目集规范族准备
void Initialize_Project() {
    int num = 0;
    for (auto obj : productions) {
        //if 产生式为A->ε,只能生成A->·
        if (obj.right.at(0).compare("ε") == 0) {
            Project pro(obj.index, num);
            num++;
            pro.type = "归约项目";
            pro.rightstr = "ε";
            continue;
        }
        //不为空集，正常初始化
        for (int i = 0; i <= obj.right.size(); i++) {
            Project pro(obj.index, num);
            pro.index_point = i;
            //为G->E&&G->E·
            if (obj.index == 0 && i == obj.right.size()) {
                pro.type = "接受项目";
            }
            //为E->T·
            else if (obj.right.size() == i) {
                pro.type = "归约项目";
            }
            //为E->·T
            else if (isVN(obj.right.at(i))) {
                pro.type = "待约项目";
            }
            //为E->·+T
            else {
                pro.type = "移进项目";
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
    //寻找当前项目编号的下一个项目
    int next_pro = -1;
    Project pro = find_projects(num);
    //如果项目类型为 待约项目 or 移进项目 表示有下一个
    if (pro.type == "待约项目" || pro.type == "移进项目") {
        for (auto obj : projects) {
            //如果来自同一个产生式&&是当前项目的下一个输入
            if (pro.index == obj.index && obj.index_point == pro.index_point + 1) {
                return obj.number;
            }
        }
    }
    else {
        cout << "出现错误" << endl;
        return next_pro;
    }
}
void Project_Set_Specification_Family() {
    //求I0
    Family pro_family(0);
    //记录左侧的非终结符
    vector<string> left;
    left.push_back(projects.at(0).leftstr);
    //记录右侧下一位的非终结符
    vector<string> right;
    right.push_back(projects.at(0).rightstr);
    //G'->E先加入到I0中，
    pro_family.project_num.push_back(projects.at(0).number);
    //判断是否都包含
    bool pro_family_all = true;
    do {
        //默认为最后一次
        pro_family_all = true;
        //找非终结符的对应的项目
        for (auto obj : right) {
            //在左侧的项目集中未出现过
            if (find(left.begin(), left.end(), obj) == left.end()) {
                for (auto obj1 : projects) {
                    //限制未非终结符
                    if (obj1.leftstr == obj && obj1.index_point == 0) {
                        pro_family.project_num.push_back(obj1.number);
                        pro_family_all = false;
                        //加入右侧
                        if (find(right.begin(), right.end(), obj1.rightstr) == right.end() && (isVN(obj1.rightstr))) {
                            right.push_back(obj1.rightstr);
                        }

                    }
                }
                //加入到左侧非终结符
                left.push_back(obj);
                break;
            }
        }
    } while (!pro_family_all);
    //I0分析完毕
    Family_table.push_back(pro_family);
    bool is_add_family = true;
    //记录所有下一个的输入
    vector<string>right_input;
    //当前的family
    int fa_ID = 0;
    do
    {
        is_add_family = true;
        right_input.clear();
        for (auto i : Family_table[fa_ID].project_num) {
            Project temp = find_projects(i);
            //当前项目为归纳项目或者接受项目时
            if (temp.type == "归约项目" || temp.type == "接受项目")
                continue;
            if (find(right_input.begin(), right_input.end(), temp.rightstr) == right_input.end()) {
                right_input.push_back(temp.rightstr);
            }
        }
        //依次遍历右侧的输入
        for (string obj : right_input) {
            //计算在读取下一个字符后蔟
            int i = Family_table.size();
            Family new_Family(i);
            //查看当前蔟中的读取后的下一个蔟
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
            // 每轮循环直到CLOSURE(I)不再增大为止
            int cur = 0;
            //避免 S->.A S->a A->.S  又添加S的项目，循环往复
            set<string> left_;
            for (int i : new_Family.project_num) {
                Project temp = find_projects(i);
                //使用为头
                if (temp.index_point == 0) {
                    right_input.push_back(temp.leftstr);
                }
            }
            //添加新的Family中的后继项目
            pro_family_all = true;
            do
            {
                pro_family_all = true;
                //新的右侧的输入
                vector<string> new_right;
                int new_Family_size = new_Family.project_num.size();
                for (int j = cur; j < new_Family_size; j++) {
                    Project temp = find_projects(new_Family.project_num.at(j));
                    //右侧为非终结符
                    if (isVN(temp.rightstr)) {
                        //E->.E的情况
                        if (temp.leftstr == temp.rightstr && temp.index == 0) {
                            continue;
                        }
                        else if (left_.count(temp.rightstr) > 0) {
                            continue;
                        }
                        //更新
                        else {
                            left_.insert(temp.rightstr);
                        }
                        //添加进去
                        new_right.push_back(temp.rightstr);
                    }
                }
                for (string obj1 : new_right) {
                    //找到E->S.A 中的A的项目
                    for (auto obj2 : projects) {
                        if (obj1 == obj2.leftstr && obj2.index_point == 0) {
                            new_Family.project_num.push_back(obj2.number);
                            //可能读取的还会有新的
                            pro_family_all = false;
                        }
                    }
                }
                cur = new_Family_size;
                new_right.clear();
            } while (!pro_family_all);

            //判断新建的状态是否和已经建立的状态重合
            bool flag_tmp = false;
            for (auto obj3 : Family_table) {
                //这里不但要包含，而且应该大小也相同
                //&&new_Family.project_num.size()==obj3.project_num.size()
                if (new_Family == obj3 && new_Family.project_num.size() == obj3.project_num.size()) {
                    flag_tmp = true;
                    Goto go(obj, fa_ID, obj3.family_num);
                    gototables.push_back(go);
                    break;
                }
            }
            if (!flag_tmp) {
                //没有重复的
                Family_table.push_back(new_Family);
                Goto go(obj, fa_ID, new_Family.family_num);
                gototables.push_back(go);
                is_add_family = false;

            }
        }
        //下一个
        fa_ID++;
        if (fa_ID >= Family_table.size())
            break;
        else
            is_add_family = false;


    } while (!is_add_family);
}
void ActionTable() {
    //项目蔟
    for (auto obj : Family_table) {
        //项目蔟中的项目
        for (int obj1 : obj.project_num) {
            Project temp = find_projects(obj1);
            //当为移进项目而且右侧为终结符时
            if (temp.type == "移进项目" && (!isVN(temp.rightstr))) {
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
                //终结符 蔟号 <goto>
                Action act(temp.rightstr, obj.family_num, action);
                Actiontables.push_back(act);
            }
            //G'->E. 接受项目，属于Ik, Action[k, #] = acc
            else if (temp.type == "接受项目") {
                Action act("#", obj.family_num, "acc");
                Actiontables.push_back(act);
            }
            //归约项目 for all a ∈ FOLLOW(A), do Action[k, a] = rj (j是产生式A->a的编号)
            else if (temp.type == "归约项目") {
                int follow = 0;
                for (auto obj2 : fcollections) {
                    //如果follow集中的非终结符对应到当前项目的终结符
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
        //获取当前项目蔟中的所有项目
        Project temp = find_projects(obj);
        if (temp.type == "归约项目") {
            reduce++;
        }
        else if (temp.type == "移进项目")
        {
            move++;
        }
    }
    //当存在移进和规约时
    if (move > 0 && reduce > 0)
    {
        //移进-归约冲突
        return "MRCONFLICT";
    }
    //或者存在二个及以上的规约
    else if (reduce >= 2) {
        //归约-归约冲突
        return "RRCONFLICT";
    }
    else {
        //无冲突
        return "NONECONFLICT";
    }
}

bool judgeG() {

    bool judgeG = true;
    vector<string>move;//存放移进的终结符
    vector<string>reduce;//存放规约的非终结符
    for (auto obj : Family_table) {
        //查看什么冲突
        string conflict = judege_conflict(obj);
        if (conflict == "MRCONFLICT") {
            //如果出现移进-规约冲突
            //A->B. A->B.*
            //{*} ∩ follow(A)！=空集
            cout << obj.family_num << "中存在移进-规约冲突\t" ;
            move.clear();
            reduce.clear();
            for (auto obj1 : obj.project_num) {
                Project temp = find_projects(obj1);
                if (temp.type == "移进项目") {
                    move.push_back(temp.rightstr);
                }
                else if (temp.type == "归约项目")
                    reduce.push_back(temp.leftstr);
            }
            string fb;
            for (auto obj1 : reduce) {
                first_follow temp(obj1);
                vector<first_follow>::iterator ff = find(fcollections.begin(), fcollections.end(), temp);
                //遍历终结符
               
                for (auto obj2 : move) {
                    fb = obj2;
                    if (find((*ff).vfollow.begin(), (*ff).vfollow.end(), obj2) != (*ff).vfollow.end()) {

                        judgeG = false;
                        break;
                    }
                   
                }
                if (judgeG == false) 
                {
                    cout <<"终结符的"<<obj1 << "的Follow集和非终结符的" << fb << "的first集" << "的交集不为空都有"<<fb << endl;
                    break;
                }
                else
                {
                    cout << "终结符的" << obj1 << "的Follow集和非终结符的" << fb << "的first集" << "的交集为空" << endl;
                }
            }

        }
        else if (conflict == "RRCONFLICT") {
            //A->B.  C->D.
            //follow(A) ∩ follow(C)！=空集
            cout << obj.family_num << "中存在归约-归约冲突" << endl;
            reduce.clear();
            for (auto obj1 : obj.project_num) {
                Project temp = find_projects(obj1);
                if (temp.type == "归约项目")
                    //获得左侧
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
                    //求交集
                    vector<string> target;
                    target.resize(min((*fB).vfollow.size(), (*fA).vfollow.size()));
                    vector<string>::iterator itend = set_intersection(
                        (*fB).vfollow.begin(), (*fB).vfollow.end(),
                        (*fA).vfollow.begin(), (*fA).vfollow.end(),
                        target.begin());
                    //说明有交集
                    if (target.begin() != target.end())
                    {
                        judgeG = false;
                        fb = reduce.at(j);
                        break;
                    }
                }
                if (judgeG == false)
                {
                    cout <<"终结符的" << obj1 << "的Follow集和终结符的" << fb << "的Follow集" << "的交集不为空" << endl;
                    break;
                }
                else {
                    cout <<"终结符的" << obj1 << "的Follow集和终结符的" << fb << "的Follow集" << "的交集为空集" << endl;
                }
            }
        }
        if (judgeG == false) {
            cout << "不是SLR文法" << endl;
            break;
        }

    }
    if (judgeG) {
        cout << "是SLR文法" << endl;

    }
    return judgeG;
}


void analysis_SLR() {
    inputIstr();
    //压入终止符号和文法的开始符合
    GAnalasis.push("#");
    Family_stack.push("I0");
    int i = 0, steps = 0;
    cout << wait_ananly << " 的分析过程如下：" << endl;
    cout << setw(16) << left << "过程计数";
    cout << setw(20) << left << "语法分析栈";
    cout << setw(20) << left << "状态分析栈";
    cout << setw(20) << left << "剩余未匹配的字串";
    cout << setw(20) << left << "操作";
    cout << endl;
    for (int p = 0; p < 12; p++)
        cout << "———— ";
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

        char cur_c = wait_ananly[i];   //当前指示字符
        //取栈顶元素
        if (GAnalasis.empty()) {
            cout << "栈为空！！！" << endl;
            return;
        }

        bool is_id = false;
        int add_i = 0;
        string str;
        //如果有id
        if ((Finalization.count("id") > 0) && (cur_c >= 'a' && cur_c <= 'z') || (cur_c >= '0' && cur_c <= '9')) {
            //匹配成功
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
        //取项目蔟顶
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
            //移进操作
            i+=add_i;

            cout << setw(20) << left << "移进"<<endl;
            int next_state = stoi(act.F2S.substr(1));
            //状态压栈
            string next_I = "I" + to_string(next_state);
            Family_stack.push(next_I);
            //语法压栈

            GAnalasis.push(str);
        }
        else if (act.F2S[0] == 'r') {
            //归约
            int next_Reduce = stoi(act.F2S.substr(1));
            production pro;
            for (auto obj : productions) {
                if (next_Reduce == obj.index) {
                    pro = obj;
                    break;
                }
            }
            string prostr = "归约:" + pro.left + "->";
            for (auto obj : pro.right) {
                prostr += obj;
            }
            cout << setw(20) << left << prostr << endl;
            //进行归约操作 如F->id  规约后F进分析栈中
            for (auto obj : pro.right) {
                GAnalasis.pop();
                Family_stack.pop();
            }
            int top_FS = stoi(Family_stack.top().substr(1).c_str());
            GAnalasis.push(pro.left);
            for (auto obj1 : gototables) {
                if (pro.left == obj1.nonterminal && obj1.state == top_FS) {
                    //新的状态压栈
                    string next_I = "I" + to_string(obj1.FN);
                    Family_stack.push(next_I);
                    break;
                }
            }
        }
        else if (act.F2S == "acc") {
            //acc 结束
            cout << setw(20) << left << "接受";
            cout << endl;
            for (int p = 0; p < 12; p++)
                cout << "———— ";
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
            cout << "· ";
        }
        cout << prod.right[j] << " ";
    }
    if (i == prod.right.size())
    {
        cout << "·";
    }
    cout << endl;
}
void print_family_table() {
    cout << "规范蔟为" << endl;
    for (auto obj : Family_table) {
        cout << "\t  I-" << obj.family_num << endl;
        cout << "编号\t类型\t   表达式" << endl;
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
    cout << "\t项目表" << endl;
    cout << "项目编号\t类型\t   表达式" << endl;
    for (auto obj : projects) {
        obj.print();
    }
}

void printGototable() {
    cout << endl;
    cout << "\t\tGOTOtable" << endl;
    for (auto obj : gototables) {
        cout << "\t[ I" << obj.state << " , " << obj.nonterminal << "] ——> I" << obj.FN << endl;
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
        //扫描action 
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
        //扫描GOto
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



