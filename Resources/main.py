import sys
import traceback
import ReadDir

def main():
	filepath = "cfg";
	file = ReadDir.GetDir();
	file.Open(filepath);
	file.WriteFile("../../xxy003/Classes/config/bt_list.cpp")

if __name__ == "__main__":
	try:
		main()
	except Exception, e:
		sys.stderr.write("Exception: " + e.message)
		sys.stderr.write("\n\n==== Python Exception ==== \n")
		traceback.print_exc();
		sys.stderr.write("==== Python Exception ==== \n\n")
		sys.exit(1)

