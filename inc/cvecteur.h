#pragma once

#include <array>
#include <cstddef>

#include <eigen3/Eigen/Dense>

template <typename T, std::size_t N>

class CVecteur {
    private:
        std::array<T, N> stockage_;
    public:
        CVecteur() = default;
        ~CVecteur() = default;
        CVecteur(const CVecteur& other) = default;
        CVecteur(CVecteur&& other) = default;
        /**
         * Surcharge [] pour accès lecture/écritue
         */
        T& operator[](std::size_t i) { return stockage_[i]; }
        const T& operator[](std::size_t i) const { return stockage_[i]; }
        
        /**
         * Surcharge + pour addition element par element
         */
        CVecteur operator+(const CVecteur& other) const
        {
            CVecteur res;
            for(size_t i=0;i<N;i++)
            {
                res.stockage_[i] = stockage_[i] + other.stockage_[i];
            }
            return res;
        }

        /**
         * Surcharge - pour soustraction element par element
         */
        CVecteur operator-(const CVecteur& other) const
        {
            CVecteur res;
            for(std::size_t i=0; i<N; ++i) 
            {
                res.stockage_[i] = stockage_[i] - other.stockage_[i];
            }
            return res;
        }
        
        /**
         * Surcharge * pour multpilication element par element
         */
        CVecteur operator*(T scalar) const
        {
            CVecteur res;
            for(std::size_t i=0; i<N; ++i) 
            {
                res.stockage_[i] = stockage_[i] * scalar;
            }
            return res;
        }

        /**
         * Produit scalaire de deux CVecteur
         * @return La valeur du produit scalaire
         */
        T dot(const CVecteur& other) const
        {
            T res = 0;
            for(std::size_t i=0; i<N; ++i) 
            {
                res += stockage_[i] * other.stockage_[i];
            }
            return res;
        }

        /**
         * Calcule la norme
         * @return La norme du vecteur CVecteur
         */
        T norm() const
        {
            return sqrt(this->dot(*this));
        }

        /**
         * Transforme le vecteur en matrice Eigen (zéro copie)
         * @return La matrice Eigen correspondante
         */
        Eigen::Matrix<T,N,1> toEigen() const
        {
            return Eigen::Map<const Eigen::Matrix<T, N, 1>>(stockage_.data());
            
        }
};
