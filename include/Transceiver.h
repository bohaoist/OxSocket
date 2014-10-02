#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_

/**
 * virtual BaseClass for Classes that should provide a send() and recv() method
 */
class Transceiver {
protected:
	Transceiver();
public:
	virtual ~Transceiver();
	virtual int send(const char*, const unsigned, const int = 0) = 0;
	virtual int recv(char *, const unsigned, const int = 0) = 0;
};

#endif
