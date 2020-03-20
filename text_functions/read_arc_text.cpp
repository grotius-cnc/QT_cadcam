#include "read_arc_text.h"
#include <core_functions/variables.h>

read_arc_text::read_arc_text(double x, double y, double z)
{
    //QFile file_in(QDir::currentPath() + "/" + filename_in );

    QFile file_in(filename_in );
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in(&file_in);    // file to read

    while(!in.atEnd()) {
        QString line = in.readLine();

            if( (line.contains("ARC", Qt::CaseSensitive)) && (!line.contains("$DIMARCSYM", Qt::CaseSensitive)) )
            {
                int_cad_array[cad_counter][0] = 3;                              //id
                //int_cad_array[cad_counter][1] = color;                          //color
                int_cad_array[cad_counter][2] = 1;                              //line width
                int_cad_array[cad_counter][3] = 1;                              //select
                arctrigger = 1;
            }
            if(arctrigger){
                if(line.contains(" 62", Qt::CaseSensitive)){                    //colorcode line
                    colorcode_line = linenumber + 1;
                }
                if(linenumber == colorcode_line){                               //fill array
                    int_cad_array[cad_counter][1] = line.toInt();
                }
                if(line.contains(" 10", Qt::CaseSensitive)){
                    x_center_line = linenumber + 1;                             //x start line
                }
                if(linenumber == x_center_line){
                    double_cad_array[cad_counter][6] = line.toDouble() + x;     //fill array
                }
                if(line.contains(" 20", Qt::CaseSensitive)){
                    y_center_line  = linenumber + 1;
                }
                if(linenumber == y_center_line){
                    double_cad_array[cad_counter][7] = line.toDouble() + y;
                }
                if(line.contains(" 30", Qt::CaseSensitive)){
                    z_center_line  = linenumber + 1;
                }
                if(linenumber == z_center_line){
                    double_cad_array[cad_counter][8] = line.toDouble() + z;
                }
                if(line.contains(" 40", Qt::CaseSensitive)){
                    radius_line = linenumber + 1;
                }
                if(linenumber == radius_line){
                    double_cad_array[cad_counter][9] = line.toDouble();
                }

                if(line.contains(" 50", Qt::CaseSensitive)){
                    start_angle_line = linenumber + 1;
                }
                if(linenumber == start_angle_line){
                    double_cad_array[cad_counter][10] = line.toDouble();
                }

                if(line.contains(" 51", Qt::CaseSensitive)){
                    end_angle_line = linenumber + 1;
                }
                if(linenumber == end_angle_line){
                    double_cad_array[cad_counter][11] = line.toDouble();
                    arctrigger = 0;
                    cad_counter++;
                }
            }

    linenumber++;
    }
    file_in.close();
}
