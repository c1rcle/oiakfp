#pragma once

#include <iostream>
#include <vector>

class ByteArray
{
public:

    ///ByteArray static class default constructor.
    ByteArray() = default;

    /// Copies bytes to a container.
    /// \param source - source byte array.
    /// \param size - array element count.
    /// \param destination - destination vector.
    static void putBytes(const u_char * source, u_int size, std::vector<u_char> &destination);

    /// Sets specified bit value.
    /// \param array - byte array which single bit will be changed.
    /// \param position - bit position.
    /// \param value - new value.
    static void setBit(std::vector<u_char> &array, u_int position, bool value);

    /// Returns specified bit value.
    /// \param array - byte array which single bit will be retrieved.
    /// \param position - bit position.
    /// \return true if bit equals 1, otherwise false.
    static bool getBit(std::vector<u_char> &array, u_int position);

    /// Shifts a vector of bytes 'shift' times right.
    /// \param vector - vector which contents are going to be shifted.
    /// \param shift - bit shift count.
    static void shiftVectorRight(std::vector<u_char> &vector, int shift);

    /// Shifts a vector of bytes 'shift' times left.
    /// \param vector - vector which contents are going to be shifted.
    /// \param shift - bit shift count.
    static void shiftVectorLeft(std::vector<u_char> &vector, int shift);

    /// Adds bytes from two containers together (result stored in first).
    /// \param first - first addition operand (vector).
    /// \param second - second addition operand (vector).
    /// \return 0 - if there is no carry, 1 - otherwise.
    static bool addBytes(std::vector<u_char> &first, const std::vector<u_char> &second);

    ///
    /// \brief addBytesEqSize
    /// \param first
    /// \param second
    /// \return
    ///
    static bool addBytesEqSize(std::vector<u_char> &first, const std::vector<u_char> &second);

    /// Subtracts bytes from two containers (result stored in first).
    /// \param first - first subtraction operand (vector).
    /// \param second - second subtraction operand (vector).
    /// \return 0 - if there is no carry, 1 - otherwise.
    static bool subtractBytes(std::vector<u_char> &first, const std::vector<u_char> &second);

    /// Comparision subtracts second argument from first.
    /// \param first - byte array for comparision.
    /// \param second - byte array for comparision.
    /// \return 0 if first and second argument is the same, -1 if second is greater and 1 if first is greater.
    static int compare(const std::vector<u_char> &first, const std::vector<u_char> &second);

    static bool checkIfZero(const std::vector<u_char> &first);

    static std::vector<u_char> createOne(unsigned int size);
    static std::vector<u_char> createValue(unsigned int size, u_char value);

    ///
    /// \brief multiplyBytes multiply vector by vector
    /// \param first[in|out]
    /// \param second
    /// \return
    ///
    static void multiplyBytes(std::vector<u_char> &first, const std::vector<u_char> &second);

    ///
    /// \brief multiplyBytesByByte multiply vector by one byte.
    /// \param first[in|out]
    /// \param second
    /// \return
    ///
    static void multiplyBytesByByte(std::vector<u_char> &first, u_char multiplyer);

    ///
    /// \brief findOldestOnePostition function check where the highest one is located and returns
    ///        position of its
    /// \param first
    /// \return
    ///
    static unsigned int findOldestOnePostition(const std::vector<u_char> &first);

    ///
    /// \brief cutVector function cat vector to specified size in bits.
    /// \param first
    /// \param sizeInBits
    /// \return
    ///
    static unsigned int cutVector(std::vector<u_char> &first, unsigned int sizeInBits);
};

std::ostream& operator <<(std::ostream& str, const std::vector<u_char>& obj);
std::ostream& operator <<(std::ostream& str, const std::vector<std::vector<u_char> >& obj);
