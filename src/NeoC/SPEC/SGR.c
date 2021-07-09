#include "SGR.h"

void _Setup() {
	SGR = (_SGR){
		.SET = {
			.BOLD				= CSI.GenerateSGR(1),
			.DIM				= CSI.GenerateSGR(2),
			.UNDERLINED			= CSI.GenerateSGR(4),
			.BLINK				= CSI.GenerateSGR(5),
			.REVERSE			= CSI.GenerateSGR(7),
			.HIDDEN				= CSI.GenerateSGR(8),
		},

		.RESET = {
			.ALL				= CSI.GenerateSGR(0),
			.BOLD				= CSI.GenerateSGR(21),
			.DIM				= CSI.GenerateSGR(22),
			.UNDERLINED			= CSI.GenerateSGR(24),
			.BLINK				= CSI.GenerateSGR(25),
			.REVERSE			= CSI.GenerateSGR(27),
			.HIDDEN				= CSI.GenerateSGR(28),
		},

		.TEXT = {
			.DEFAULT			= CSI.GenerateSGR(39),
			.BLACK				= CSI.GenerateSGR(30),
			.RED				= CSI.GenerateSGR(31),
			.GREEN				= CSI.GenerateSGR(32),
			.YELLOW				= CSI.GenerateSGR(33),
			.BLUE				= CSI.GenerateSGR(34),
			.MAGENTA			= CSI.GenerateSGR(35),
			.CYAN				= CSI.GenerateSGR(36),
			.LIGHT_GRAY			= CSI.GenerateSGR(37),
			.DARK_GRAY			= CSI.GenerateSGR(90),
			.LIGHT_RED			= CSI.GenerateSGR(91),
			.LIGHT_GREEN		= CSI.GenerateSGR(92),
			.LIGHT_YELLOW		= CSI.GenerateSGR(93),
			.LIGHT_BLUE			= CSI.GenerateSGR(94),
			.LIGHT_MAGENTA		= CSI.GenerateSGR(95),
			.LIGHT_CYAN			= CSI.GenerateSGR(96),
			.WHITE				= CSI.GenerateSGR(97),
		},

		.BACKGROUND = {
			.DEFAULT			= CSI.GenerateSGR(49),
			.BLACK				= CSI.GenerateSGR(40),
			.RED				= CSI.GenerateSGR(41),
			.GREEN				= CSI.GenerateSGR(42),
			.YELLOW				= CSI.GenerateSGR(43),
			.BLUE				= CSI.GenerateSGR(44),
			.MAGENTA			= CSI.GenerateSGR(45),
			.CYAN				= CSI.GenerateSGR(46),
			.LIGHT_GRAY			= CSI.GenerateSGR(47),
			.DARK_GRAY			= CSI.GenerateSGR(100),
			.LIGHT_RED			= CSI.GenerateSGR(101),
			.LIGHT_GREEN		= CSI.GenerateSGR(102),
			.LIGHT_YELLOW		= CSI.GenerateSGR(103),
			.LIGHT_BLUE			= CSI.GenerateSGR(104),
			.LIGHT_MAGENTA		= CSI.GenerateSGR(105),
			.LIGHT_CYAN			= CSI.GenerateSGR(106),
			.WHITE				= CSI.GenerateSGR(107),
		},
	};
}

_SGR SGR = {
	._Setup = _Setup,
};
