#ifndef CHARENCODING_H_
#define CHARENCODING_H_

class char_encoding {

public:
	unsigned short get_byte(char ch);
	char get_char(unsigned short byte);

};

#endif /* CHARENCODING_H_ */
