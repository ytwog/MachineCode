#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    res = "";
    first = 0, second = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::approved()
{
    for(int t = 0; t < 2; t++)
    {
        QString Str;
        if(t)
        {
            Str = ui->SecondEdit->text();
        }
        else
        {
            Str = ui->FirstEdit->text();
        }
        bool INT = true;
        bool num = false;
        short Zero = false;//zero == 1 ? next should be '.' , else doesn't matter.
        for(int i = 0; i < Str.length(); i++)
        {
            if((i == 0) && (Str[i] == '-'))
            {
                continue;
            }
            if((Str[i] == '.') || (Str[i] == ','))
            {
                if(INT)
                {
                    if(num)
                    {
                        Zero = 2;
                        INT = false;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else if(Str[i] == '0')
            {
                num = true;
                if(INT && Zero == 0)
                {
                    Zero = 1;
                }
                else
                {
                    Zero = 2;
                }
            }
            else if(Str[i] == '1')
            {
                num = true;
                if(INT)
                {
                    if(Zero == 1)
                    {
                        return false;
                    }
                    else
                    {
                        Zero = 2;
                    }
                }
                else
                {
                    Zero = 3;
                }
            }
            else
            {
                return false;
            }
        }
        if((INT == 0) && (Zero != 3))
        {
            return false;
        }
    }
    return true;
}

QString normal(QString data)
{
    QString res = "";
    for(int i = 0; i < data.length(); i++)
    {
        if(i == 0)
        {
            if(data[i] == '-')
            {
                res += "1 ";
                continue;
            }
            else
            {
                res += "0 ";
            }
        }
        if((data[i] == '.') || (data[i] == ','))
        {
            continue;
        }
        res += data[i];
    }

    return res;
}

QString oppos(QString data)
{
    QString res = "";
    for(int i = 0; i < data.length(); i++)
    {
        if(i == 0)
        {
            if(data[i] == '-')
            {
                res += "1 ";
                continue;
            }
            else
            {
                res += "0 ";
            }
        }
        if((data[i] == '.') || (data[i] == ','))
        {
            continue;
        }
        if(data[i] == '1')
        {
            res += '0';
        }
        else
        {
            res += '1';
        }
    }
    return res;
}

QString addit(QString data)
{
    int INT = 0;
    bool ZERO = true;
    int sum1 = 1;
    for(int i = data.length() - 1; i > 1; i--)
    {
        if(data[i] == '1')
        {
            sum1++;
        }
        //
        if(sum1 == 1)
        {
            data[i] = '1';
            sum1 = 0;
        }
        else if(sum1 == 2)
        {
            data[i] = '0';
            sum1 = 1;
        }
        else
        {
            sum1 = 0;
        }
    }
    return data;
}



QString final(QString data)
{
    QString res = "";
    QString temp = "";
    int sum1 = 1;
    for(int i = data.length() - 1; i > 2; i--)
    {
        if(data[i] == '1')
        {
            sum1++;
        }
        //
        if(sum1 == 1)
        {
            data[i] = '1';
            sum1 = 0;
        }
        else if(sum1 == 2)
        {
            data[i] = '0';
            sum1 = 1;
        }
        else
        {
            sum1 = 0;
        }
    }
    return data;
}

void MainWindow::on_pushButton_clicked()
{
    if(approved())
    {
        ui->str1->setText(normal(ui->FirstEdit->text()));
        ui->str2->setText(normal(ui->SecondEdit->text()));

        QString opp1 = oppos(ui->FirstEdit->text());
        QString opp2 = oppos(ui->SecondEdit->text());

        ui->opp1->setText(opp1);
        ui->opp2->setText(opp2);

        QString add1 = opp1;
        QString add2 = opp2;

        add1 = addit(opp1);
        add2 = addit(opp2);

        ui->add1->setText(add1);
        ui->add2->setText(add2);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Неверно введены одно или несколько чисел!");
        msgBox.exec();
    }
}

int fromTenth(int inp)
{
    QString res = "";
    while(inp)
    {
        res = (QString::number(inp % 2) + res);
        inp /= 2;
    }
    return res.toInt();
}

QString sum(QString str1, QString str2)
{
    QString temp = "";
    QString res = "";
    int len = str1.length();
    int summ = 0;
    for(int i = len - 1; i >= 0 ; i--)
    {
        if(str1[i] == '1')
        {
            summ++;
        }
        if(str2[i] == '1')
        {
            summ++;
        }

        if(summ == 2)
        {
            temp += '0';
            summ = 1;
        }
        else if(summ == 1)
        {
            temp += '1';
            summ = 0;
        }
        else if(summ == 0)
        {
            temp += '0';
            summ = 0;
        }
        else
        {
            temp += '1';
            summ = 1;
        }
    }

    if(summ == 0)
    {
        res += "0";
    }
    else if(summ == 1)
    {
        res += "1";
    }

    res += temp[len - 1] + " ";

    for(int i = len - 2; i >= 0; i--)
    {
        res += temp[i];
    }
    return res;
}



QString translate(int rank, QString data)
{
    bool Neg = data[1] == '1' ? true : false;
    data.remove(0, 3);
    if(Neg)
    {
        data.insert(0, '-');
    }
    if(rank)
    {
        data.insert(rank + Neg, ',');
    }
    if(Neg)
    {
        while(data[1] == '0')
        {
            data.remove(1, 1);
        }
    }
    else
    {
        while(data[0] == '0')
        {
            data.remove(0, 1);
        }
    }
    if(data[data.length() - 1] == ',')
    {
        data.remove(data.length() - 1, 1);
    }
    if((data.length() == 0) || (data.length() == 1 && Neg))
    {
        data.append('0');
    }
    return data;
}


void MainWindow::on_calculate_clicked()
{
    res = "Запишем числа в нормализованном виде в разрядной сетке:\n";
    if(approved())
    {
        bool globalNeg = false;
        QString _first = ui->FirstEdit->text();
        QString _second = ui->SecondEdit->text();
        bool Neg1 = _first[0] == '-';
        bool Neg2 = _second[0] == '-';
        int comma1 = _first.indexOf(',') + _first.indexOf('.') + 1;
        int comma2 = _second.indexOf(',') + _second.indexOf('.') + 1;
        int rank1;
        int rank2;
        if(Neg1)
        {
            _first.remove(0, 1);
        }
        if(Neg2)
        {
            _second.remove(0, 1);
        }
        if(Neg1 && Neg2)
        {
            globalNeg = true;
        }
        if(_first[0] == '0')
        {
            rank1 = -_first.indexOf('1') + 2;
        }
        else
        {
            int pos1 = _first.indexOf('1');
            int posC = _first.indexOf('.');
            if(posC == -1)
            {
                posC = _first.indexOf(',');
            }
            if(posC == -1)
            {
                rank1 = _first.length();
            }
            else
            {
                rank1 = posC;
            }
        }
        if(_second[0] == '0')
        {
            rank2 = -_second.indexOf('1') + 2;
        }
        else
        {
            int pos1 = _second.indexOf('1');
            int posC = _second.indexOf('.');
            if(posC == -1)
            {
                posC = _second.indexOf(',');
            }
            if(pos1 < posC)
            {
                rank2 = posC;
            }
            else
            {
                rank2 = _second.length();
            }
        }
        // Первое число
        QString first1 = "";
        res += "1) ";
        first1 += QString::number(rank1 < 0) + " ";
        int rank1D = fromTenth(abs(rank1));
        for(int i = 0; i < 4 - QString::number(rank1D).length(); i++) {first1 += "0";}
        first1 += QString::number(rank1D);
        first1 += " " + QString::number(Neg1) + " ";
        bool ZERO = true;
        QString Norm1 = "";
        for(int i = 0; i < _first.length(); i++)
        {
            if((_first[i] == '.') || (_first[i] == ','))
            {
                continue;
            }
            if(_first[i] == '1')
            {
                ZERO = false;
            }
            if(!ZERO && (_first[i] != '.' || _first[i] != ','))
            {
                Norm1 += _first[i];
            }
        }
        ZERO = true;
        QString Norm2 = "";
        for(int i = 0; i < _second.length(); i++)
        {
            if((_second[i] == '.') || (_second[i] == ','))
            {
                continue;
            }
            if(_second[i] == '1')
            {
                ZERO = false;
            }
            if(!ZERO && (_second[i] != '.' || _second[i] != ','))
            {
                Norm2 += _second[i];
            }
        }
        res += first1;
        int len = Norm1.length() > Norm2.length() ? Norm1.length() : Norm2.length();
        res += Norm1;
        for(int i = 0; i < len - Norm1.length(); i++) {res += "0";}
        // Второе число
        QString second1 = "";
        res += "\n2) ";
        second1 += QString::number(rank2 < 0) + " ";
        int rank2D = fromTenth(abs(rank2));
        for(int i = 0; i < 4 - QString::number(rank2D).length(); i++) {second1 += "0";}
        second1 += QString::number(rank2D);
        second1 += " " + QString::number(Neg2) + " ";
        res += second1;
        res += Norm2;
        for(int i = 0; i < len - Norm2.length(); i++) {res += "0";}
        res += "\nВыравнивание порядков:";
        res += "\n1) ";
        if(rank1 > rank2)
        {
            QString temp = "";
            res += first1;
            //res += QString::number(Neg1) + " ";
            for(int i = 0; i < rank1 - rank2; i++){temp += '0';}
            temp += Norm2;
            Norm2 = temp;
            temp = "";
            for(int i = 0; i < Norm2.length(); i++)
            {
                if(Norm1.length() < i + 1)
                {
                    temp += '0';
                }
                else
                {
                    temp += Norm1[i];
                }
            }
            Norm1 = temp;
            res += Norm1;
            res += "\n2) ";
            res += first1;
            //res += QString::number(Neg2) + " ";
            res += Norm2 + " ";
            rank2 = rank1;
        }
        else
        {
            QString temp = "";
            for(int i = 0; i < rank2 - rank1; i++){temp += '0';}
            temp += Norm1;
            Norm1 = temp;
            temp = "";
            for(int i = 0; i < Norm1.length(); i++)
            {
                if(Norm2.length() < i + 1)
                {
                    temp += '0';
                }
                else
                {
                    temp += Norm2[i];
                }
            }
            Norm2 = temp;
            res += second1;
            res += QString::number(Neg1) + " ";
            res += Norm1;
            res += "\n2) ";
            res += second1;
            res += QString::number(Neg2) + " ";
            res += Norm2 + " ";
            rank1 = rank2;
        }
        res += "\nПеревод чисел в обратный код\n1      = ";
        if(Neg1 && !globalNeg)
        {
            Norm1 = oppos(Norm1);
            Norm1.remove(0, 2);
        }
        res += '0' + QString::number(Neg1) + " " + Norm1 + "\n2      = ";
        if(Neg2 && !globalNeg)
        {
            Norm2 = oppos(Norm2);
            Norm2.remove(0, 2);
        }
        res += '0' + QString::number(Neg2) + " " + Norm2;
        QString sum1 = sum(QString::number(Neg1) + Norm1, QString::number(Neg2) + Norm2);
        res += "\nСумма = " + sum1;
        if(!Neg1 || !Neg2)
        {
            if(Neg1)
            {
                sum1 = final(sum1);
            }
            if(Neg2)
            {
                sum1 = final(sum1);
            }
        }
        else
        {
            sum1[0] = '0';
            sum1[1] = '1';
        }
        QString fin = sum1;
        sum1.remove(3, sum1.length() - 3);
        res += "\nПеревод в прямой код:\n";
        res += fin;
        res += "\nРезультат: " + translate(rank1, fin);
        ui->textBrowser->setText(res);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Неверно введены одно или несколько чисел!");
        msgBox.exec();
    }
}
