// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bullet.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngulya <marvin@42.fr>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/05 18:30:54 by ngulya            #+#    #+#             //
//   Updated: 2017/11/05 18:30:54 by ngulya           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bullet.hpp"

Bullet::Bullet(){
	posx = -1;
	posy = -1;
	bullet = '\'';
}

Bullet::~Bullet(){}

Bullet 		&Bullet::operator=(Bullet &pl){
	posx = pl.posx;
	posy = pl.posy;
	bullet = pl.bullet;
	return *this;
}

Bullet::Bullet(const Bullet &pl){
	posx = pl.posx;
	posy = pl.posy;
	bullet = pl.bullet;
}