import <conio.h>;
import <string>;
import <iostream>;
import <fstream>;
import <algorithm>;
import <map>;
import <vector>;

export module BrainFuck;

export constexpr char codeArray[9]{ '.', ',', '[', ']', '<', '>', '+', '-', '\0'};

export class BrainFuck 
{
public:
	BrainFuck() = delete;
	explicit BrainFuck(char* filename) : m_filename(filename) {
		std::ifstream readFile(filename);
		if (readFile.is_open()) {
			std::string line;
			while (std::getline(readFile, line)) {
				m_code += this->clearUp(line);
			}
			readFile.close();
			std::cout << std::format("BrainF**k Source File: {}", filename) << std::endl;
		}
		else {
			std::cout << "Cannot open the file: " << m_filename << std::endl;
		}
	}

	void compile() {
		auto braceMap{ this->buildbracemap(m_code) };
		std::vector<size_t> cells{ 0 };
		size_t codeptr{ 0 };
		size_t cellptr{ 0 };
		size_t index{ 0 };
		while (codeptr < m_code.size()) {
			auto command{ m_code[codeptr] };
			switch (command)
			{
			case '>':
				cellptr++;
				if (cellptr == cells.size()) {
					cells.push_back(0);
				}
				break;
			case '<':
				if (cellptr != 0) {
					cellptr--;
				}
				break;
			case '+':
				cells[cellptr] < 255 ? cells[cellptr]++ : cells[cellptr] = 0;
				break;
			case '-':
				cells[cellptr] < 255 ? cells[cellptr]-- : cells[cellptr] = 255;
				break;
			case '[':
				if (cells[cellptr] == 0) {
					codeptr = braceMap[codeptr];
				}
				break;
			case ']':
				if (cells[cellptr] != 0) {
					codeptr = braceMap[codeptr];
				}
				break;
			case '.':
				std::cout << (unsigned char)(cells[cellptr]);
				break;
			case ',':
				cells[cellptr] = (size_t)(_getch());
				break;
			default:
				break;
			}
			index++;
			codeptr++;
		}
	}

private:
	std::string m_filename;
	std::string m_code;

	std::string clearUp(std::string str)
	{
		std::string clearCode;
		for (const char& codeChar : str) {
			const char* charCBegin{ std::cbegin(codeArray) };
			const char* charCEnd{ std::cend(codeArray) };
			if (std::find(charCBegin, charCEnd, codeChar) != charCEnd) {
				clearCode += codeChar;
			}
		}
		return clearCode;
	}

	// 使用 std::map 模仿 Python 中的 enumerate 类方法。
	/* 使用示例：
	* code = std::string("hello world")
	* return {(0, 'h'), (1, 'e'), (2, 'l'), (3, 'l'), (4, 'o'), (5, ' '), (6, 'w'), (7, 'o'), (8, 'r'), (9, 'l'), (10, 'd')}
	*/
	std::map<size_t, char> enumerate(const std::string& code)
	{
		std::map<size_t, char> rawBraceMap;
		for (size_t i{ 0 }; i < code.size(); ++i) {
			rawBraceMap.emplace(std::pair<size_t, char>(i, code[i]));
		}
		return rawBraceMap;
	}
	std::map<size_t, size_t> buildbracemap(const std::string& code) 
	{
		std::vector<size_t> temp_bracestack{};
		std::map<size_t, size_t> bracemap{};
		auto enumerate{ this->enumerate(m_code) };
		for (auto& [position, command] : enumerate) {
			if (command == '[') {
				temp_bracestack.push_back(position);
			}
			if (command == ']') {
				auto start{ temp_bracestack.back() };
				temp_bracestack.pop_back();
				bracemap[start] = position;
				bracemap[position] = start;
			}
		}
		return bracemap;		
	}
	
};