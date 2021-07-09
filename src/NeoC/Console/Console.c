#include "Console.h"

static void SetState(uint8_t *escSeq) {
	Console.Write(String.New(escSeq));
}

static void SetColour(uint8_t *colour) {
	Console.SetState(colour);
}

static void SetDefaultColour() {
	Console.SetState(SGR.TEXT.DEFAULT);
}

static void Write(String_t *str) {
	printf("%s", String.Unpack(str));
	fflush(stdout);
}

static void WriteLine(String_t *str) {
	Console.Write(str);
	Console.NewLine();
}

static void NewLine() {
	Console.Write(String.NewChar(CC.LF));
}

static void WriteColourLine(uint8_t *colour, String_t *str) {
	Console.SetColour(colour);
	Console.WriteLine(str);
	Console.SetDefaultColour();
}

static void WriteErrorLine(String_t *str) {
	fprintf(stderr, "%s\n", String.Unpack(str));
	fflush(stderr);
}

static void Erase() {
	Console.SetState(CSI.EL(2));
}

static void ErasePrevLine() {
	Console.SetState(CSI.CPL(1));
	Console.Erase();
}

static void WriteTop(String_t *str) {
	Console.ErasePrevLine();
	Console.Write(str);
}

static void WriteTopLine(String_t *str) {
	Console.WriteTop(str);
	Console.NewLine();
}

_Console Console = {
	.SetState				= SetState,
	.SetColour				= SetColour,
	.SetDefaultColour		= SetDefaultColour,

	.Write					= Write,
	.WriteLine				= WriteLine,
	.NewLine				= NewLine,
	.WriteColourLine		= WriteColourLine,

	.WriteErrorLine			= WriteErrorLine,

	.Erase					= Erase,
	.ErasePrevLine			= ErasePrevLine,

	.WriteTop				= WriteTop,
	.WriteTopLine			= WriteTopLine,
};
