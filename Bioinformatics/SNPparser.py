from collections import OrderedDict
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import re
from sys import argv
script, pile_file, outfile_name, image_name = argv

##Open the File, Assign a handle
in_file = pd.read_table(pile_file, header=None, names=['Chromosome', 'Position', 'Reference Base', 'Coverage', 'Reads', 'Phred_Quality'])

####Wrangle the Data. First examine the 5th column and look to see if string contains any character that represents an INDEL.
#If True, that row is removed from the resulting table because of the == False option.
##The Second line checks if the remaining observations in column 5 contain at least 10 reads, indicated by the length of the string.
##The third line replaces any instance of ^ followed by any character and any $ with '' (no-space)
##This should remove any reads that would confound your data and cause false snp calls
in_file = in_file[in_file['Reads'].str.contains(r'\*|\>|\<|\+|\-') == False]
in_file = in_file[in_file['Reads'].str.len() >=10]
in_file['Reads'] = in_file['Reads'].str.replace(r'\^.|\$', '')


####This function sets up a new empty data table called snps. Then the wrangled table is iterated over the rows, setting a counter for each base and reference reads.
#The second for-loop enumerates over the characters in the string for each row in the 6th column (Phred_quality).
#If the quality score is >= 30 the function checks if the string matches either the reference forward or reverse (. ,)
#or if it matches either upper or lower-case a,c,t, or g and counts them accordingly.
snps = pd.DataFrame()
for record, row in in_file.iterrows():
    reference_read = 0
    bases={"A":0,"C":0,"G":0,"T":0}
    for i, string in enumerate(row[5]):
        if ord(string)-33 >= 30:
            if re.match("\.|,", row[4][i]):
                reference_read += 1
            elif re.match("A", row[4][i] ,re.IGNORECASE):
                bases["A"] += 1
            elif re.match("T", row[4][i] ,re.IGNORECASE):
                bases["T"] += 1
            elif re.match("C", row[4][i] ,re.IGNORECASE):
                bases["C"] += 1
            elif re.match("G", row[4][i] ,re.IGNORECASE):
                bases["G"] += 1

#This loop goes over the items in bases (A, C, T, G) and checks if the number of the same variant per row is greater than 2 (3 or above)
#For all variants with 3 or more copies, a data table is created and populated in the order it was recorded, with additional columns for the non-reference base and the frequency of the variant
#which is calculated as the function is iterating over the rows
    for q, read in bases.items():
        if read > 2:
            all_reads = len(row[4])
            frequency = (read/all_reads)
            outfile_format = pd.DataFrame(OrderedDict({"Chromosome":[row[0]],"Position":[row[1]],"Reference Base":[row[2]],"Non-Reference Base":[q],"Frequency":[frequency]}), index=[1])
            snps = snps.append(outfile_format)


### Save output to a new file, tab delimited.
snps.to_csv(outfile_name, sep='\t')


###Plot Figure
ax = snps.plot(x='Position', y='Frequency', kind='bar', figsize=(20,10), legend=True)
xticks = list(np.arange(1, len(snps), 50))
ax.set_xticks(xticks)
ax.set_xticklabels(snps.loc[xticks, 'Position'])
plt.savefig(image_name, dpi=300)
