"""A Python script that performs simple read trimming of a FASTQ file.
.. module:: Project01
   :platform: Unix, Windows
   :synopsis: This script receives as input a FASTQ file and a set of arguments
      that control trimming. A new FASTQ file is generated containing only
      trimmed reads that meet the given requirements.
.. moduleauthor:: Andrew J. Lefors
"""
from Bio import SeqIO
from sys import argv
import os
script, fq_in, fq_out, min_q, min_length = argv
reads = SeqIO.parse(fq_in, "fastq")
trimmed_reads = SeqIO.parse("tmp", "fastq")
good_reads = []
final_reads = []
read_reads = []
def get_read():
    """Extract a single read from a FASTQ file.
    Reads in a FASTQ file are stored in 4 lines that contain the
    sequence_id, nucleotide sequence, a second id, and a series of
    characters represeting quality scores.
    :param fq: A file handle for the FASTQ file
    :type fq: An io.TextIOBase object (created using the open() function).
    :return: a list containing 4 strings: the sequence ID, nucleotide sequence,
        second ID, and the quality score sequence. If there are no more
        sequences in the FASTQ file then this function returns False.
    :rtype: a list with four elements
    """
    count = 0
    for record in SeqIO.parse(fq_in, "fastq"):
        print("ID:%s\nSequence:%s\nDescription:%s\nQuality Score:%s" % (record.id, record.seq, record.description, record.letter_annotations['phred_quality']))
        count += 1
        break
    print(f"%i Reads read from {fq_in}" % count)

def read_trimmer():
    """Trims the low quality nucleotides from the front of a reads' sequences.
    This function examines the quality score of each nucleotide sequence
    starting from the first position of the sequence. When it encouters a
    high quality score it stops trimming and returns an updated read.
    :param read: A list containing for elements in this order: the sequence ID,
        the nucleotide sequence string, a secondary identifier string, and a
        quality score string.
    :type read: a list
    :param min_q:  The minimum quality score that a nucleotide must have to
        not be trimmed (e.g. 20).
    :type min_q:  integer
    :param min_size:  The minimum size that the sequence must have after
        trimming to keep the read (e.g. 25).
    :type min_size: integer
    :return: a list just like the the get_read() function returns but with the
       low-quality reads (and corresponding quality scores) trimmed off the
       front of the string. If the remaining trimmed read is smaller than the
       desired minimum read length then this function returns False.
    :rtype: a list with four elements
    """
    #This section filters reads based on quality score, appends to list only record
    #with leading base quality score >= min_q
    for record in reads:
        a = 0
        quality = record.letter_annotations['phred_quality']
        for i, q in enumerate(quality):
            if int(q) >= int(min_q):
                good_reads.append(record[a:])
                break
            else:
                a += 1
    SeqIO.write(good_reads, "tmp", "fastq")

#This section Filters Reads based on min_length
    passed = 0
    reject = 0
    for record in trimmed_reads:
        if len(record.seq) >= int(min_length):
            final_reads.append(record)
            passed += 1
        else:
            reject += 1
    SeqIO.write(final_reads, fq_out, "fastq")
    print("%i Reads were removed\n%i Reads were trimmed and kept" % (reject, passed))

def main():
    """The main function of this script.
    After trimming is completed, the fucntion prints out three status lines. The
    first indicates the total number of reads that were found. The second
    indicates how many reads were removed for being too short after trimming and
    the third indicates how many reas were trimmed and kept.
    The script will create a new FASTQ file of just the trimmed reads and name
    it according to the argument provided by the user when running the script.
    :param argv:  The incoming arguments to this script as
       provided by the sys.argv variable.  There must be four total arguments
       provided to the script must be in the following order
       - The filename for the input FASTQ file
       - The filename for the new output FASTQ file that this script creates
       - An integer for the minimum quality score. Anything below this at the
         beginning of each read's nucleotide sequence is trimmed off.
       - An integer indicating how large a read's nucleotide sequence must
         be after trimming in order to keep it.
    """
    print("Reading File...")
    get_read()
    count = 0
    for record in SeqIO.parse(fq_in, "fastq"):
        count += 1
    print(f"%i Reads found in {fq_in}" % count)
    print("Trimming File...")
    read_trimmer()
    os.remove("tmp")
    print("Done.")
main()
