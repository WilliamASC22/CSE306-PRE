PRE Process Project

Task
Build a program named csv with the functionality given below.

SUBMIT (as a single zip file named pre.zip): by 11:59 PM, Friday September 19
Activity log
To document each team member's activity and contribution to the project, each team member must contribute a .csv file with the following format to the pre.zip submission file:

DATE        UBIT      DURATION    ACTIVITY & TOOL DESCRIPTION
2021/02/04  alphonce  20 minutes  edited main.c using emacs editor to add correct #includes
Each team member's activity log file must be named with their UBIT - my file would be alphonce.csv

All the activity log files must be submitted in the same zip file as the code.

Description
NAME
csv - process data in a CSV (Comma-Separated Value) file.
SYNOPSIS
csv [-frh] [-max field] [-min field] [-mean field] [-records field value] file
DESCRIPTION
The csv program reads data from a CSV file (file), processes the contents and produces results according to command-line arguments, as follows.

-f Display the number of fields in the first record of file.

-r Display the number of data records in file. If -h is not given this is the number of lines in the file. If -h is given this is one less than the number of lines in the file.

-h Treat the first record of file as a header record rather than a data record. If this option is used then field in the following options must be specified with the title of the corresponding field from the header row (the numeric positional option is not available). If this option is not used then field in the following options must be specified with the the numeric positional option (the title of the corresponding field from the header row is not available). If an incorrect field identifier is used the program exits with error code EXIT_FAILURE.

-max field Display the maximum value in the indicated field of the data records. The first field is numbered 0. This option ignores non-numeric data in the indicated field. If there is no numeric data in the indicated field in any of the data records the program exits with error code EXIT_FAILURE. See how fields are identified when the -h option is used.

-min field Display the minimum value in the indicated field of the data records. The first field is numbered 0. This option ignores non-numeric data in the indicated field. If there is no numeric data in the indicated field in any of the data records the program exits with error code EXIT_FAILURE. See how fields are identified when the -h option is used.

-mean field Display the arithmetic mean (average) value in the indicated field of the data records. The first field is numbered 0. This option ignores non-numeric data in the indicated field. If there is no numeric data in the indicated field in any of the data records the program exits with error code EXIT_FAILURE. See how fields are identified when the -h option is used.

-records field value Display the records from file containing value in the the indicated field. The first field is numbered 0. Value is formatted according to the same rules as data in fields. See how fields are identified when the -h option is used.

EXAMPLES
These examples are based on the following sample file. In compliance with stated requirements this file is also available from the Statistics Canada archive.

Assume that '%' is the operating system prompt.

% csv -f 05020004-eng.csv
8
% csv -r 05020004-eng.csv
820
% csv -min 0 05020004-eng.csv
1998
% csv -h -min "Ref_Date" 05020004-eng.csv
1998
% csv -max 0 05020004-eng.csv
2004
% csv -h -max "Ref_Date" 05020004-eng.csv
2004
% csv -mean 7 05020004-eng.csv
10.26
% csv -h -mean "Value" 05020004-eng.csv
10.26
% csv -min 0 -max 0 -mean 7 05020004-eng.csv
1998
2004
10.26
% csv -h -min "Ref_Date" -max "Ref_Date" -mean "Value" 05020004-eng.csv
1998
2004
10.26
% csv -records 7 61.1 05020004-eng.csv
1998,Canada,"Total, all persons two years and older",Foreign television programmes,"Total, all types of television programmes",v21419952,1.1.3.1,61.1
2001,Canada,"Total, all persons two years and older",Foreign television programmes,"Total, all types of television programmes",v21419952,1.1.3.1,61.1
% csv -h -records "Value" 61.1 05020004-eng.csv
1998,Canada,"Total, all persons two years and older",Foreign television programmes,"Total, all types of television programmes",v21419952,1.1.3.1,61.1
2001,Canada,"Total, all persons two years and older",Foreign television programmes,"Total, all types of television programmes",v21419952,1.1.3.1,61.1
EXIT STATUS
EXIT_SUCCESS if execution terminates normally
EXIT_FAILURE if execution terminates abnormally
STANDARDS
The input file is expected to adhere to the rfc4180 standard for CSV files. This file is available on-line at https://www.ietf.org/rfc/rfc4180.txt
