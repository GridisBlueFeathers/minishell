/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:43:19 by svereten          #+#    #+#             */
/*   Updated: 2024/07/26 01:54:24 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef COLOR_H
# define COLOR_H

# define CLR "\x1b["
# define CLR_END "m"
# define CLR_AND ";"
# define CLR_RESET "\x1b[0m"

# define CLR_BOLD "1"
# define CLR_ITALIC "3"
# define CLR_UNDERLINE "4"

# define CLR_BLACK_FG "30"
# define CLR_RED_FG "31"
# define CLR_GREEN_FG "32"
# define CLR_YELLOW_FG "33"
# define CLR_BLUE_FG "34"
# define CLR_PURPLE_FG "35"
# define CLR_CYAN_FG "36"
# define CLR_WHITE_FG "37"

# define CLR_BLACK_BG "40"
# define CLR_RED_BG "41"
# define CLR_GREEN_BG "42"
# define CLR_YELLOW_BG "43"
# define CLR_BLUE_BG "44"
# define CLR_PURPLE_BG "45"
# define CLR_CYAN_BG "46"
# define CLR_WHITE_BG "47"

#endif // !COLOR_H
