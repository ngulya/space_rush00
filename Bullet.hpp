// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bullet.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngulya <marvin@42.fr>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/05 18:31:03 by ngulya            #+#    #+#             //
//   Updated: 2017/11/05 18:31:03 by ngulya           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef __BULLET_HPP
# define __BULLET_HPP
typedef struct {
	int x;
	int y;
} v2ib;

class Bullet{
public:
	// int		exist;
	int		posx;
	int		posy;
	char	bullet;
	Bullet();
	Bullet(const Bullet &pl);
	~Bullet();
	Bullet 		&operator=(Bullet &pl);
};

#endif