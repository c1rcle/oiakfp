#pragma once

#include <iostream>
#include <vector>

/// Static class for variable precision byte array manipulation.
class ByteArray
{
public:
    /// ByteArray static class default constructor.
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

    /// Creates a vector of bytes that represents an unsigned four-byte integer.
    /// \param value - integer to convert.
    /// \param size - number of bytes that representation should be using.
    /// \return Vector of bytes that represents an unsigned four-byte integer.
    static std::vector<u_char> getBytesFromInt(unsigned int value, unsigned int size = 4);

    /// Adds bytes from two containers together (result stored in first).
    /// \param first - first addition operand (vector).
    /// \param second - second addition operand (vector).
    /// \return 0 - if there is no carry, 1 - otherwise.
    static bool addBytes(std::vector<u_char> &first, const std::vector<u_char> &second);

    /// Adds bytes from two containers together (their size is equal).
    /// \param first - first addition operand.
    /// \param second - second addition operand.
    /// \return 0 - if there is no carry, 1 - otherwise.
    static u_char addBytesEqualSize(std::vector<u_char> &first, const std::vector<u_char> &second);

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

    /// Function that checks whether a byte container contains zero.
    /// \param first - byte array to be checked.
    /// \return 1 - if zero, 0 - otherwise.
    static bool checkIfZero(const std::vector<u_char> &first);

    /// Creates a byte array of given size which has a value of 1.
    /// \param size - array byte size.
    /// \return Byte array of given size which has a value of 1.
    static std::vector<u_char> createOne(unsigned int size);

    /// Creates a byte array of given size which has a value of 'value'.
    /// \param size - array byte size.
    /// \param value - initial value for array.
    /// \return Byte array of given size which has a value of 'value'.
    static std::vector<u_char> createValue(unsigned int size, u_char value);

    /// Multiplies bytes from two containers together (result stored in first).
    /// \param first - first multiplication operand (vector).
    /// \param second - second multiplication operand (vector).
    static void multiplyBytes(std::vector<u_char> &first, const std::vector<u_char> &second);

    /// Multiplies bytes from a single container by a single byte (result stored in that container).
    /// \param first - first multiplication operand (vector).
    /// \param multiplier - second multiplication operand (byte).
    static void multiplyBytesByByte(std::vector<u_char> &first, u_char multiplier);

    /// Divides bytes from two containers (result stored in first).
    /// \param first - first division operand (vector).
    /// \param second - second division operand (vector).
    /// \param precision - division bit precision.
    static void divideBytes(std::vector<u_char> &first, const std::vector<u_char> &second, unsigned int precision);

    /// Finds the position of highest order '1' in a byte container.
    /// \param first - container to find that position in.
    /// \return Index of highest order '1'.
    static unsigned int findHighestOrderOnePosition(const std::vector<u_char> &first);

    /// Finds the position of lowest order '1' in a byte container.
    /// \param first - container to find that position in.
    /// \return Index of lowest order '1'.
    static unsigned int findLowestOrderOnePosition(std::vector<u_char> &first);

    /// Cuts a given container to a specified bit length.
    /// \param first - byte array to cut.
    /// \param sizeInBits - bit length after being cut.
    /// \return
    static std::vector<u_char> cutVector(std::vector<u_char> &first, unsigned int sizeInBits);

    /// Converts a byte array to a binary string.
    /// \param first - byte array to convert.
    /// \param point - decimal point index.
    /// \return Byte array binary string representation.
    static std::string toBinaryString(const std::vector<u_char> &first, unsigned int point);
};

/// Overloaded output stream operator for a byte vector.
/// \param str - Output stream reference.
/// \param obj - Byte vector object reference.
/// \return - modified output stream.
std::ostream &operator <<(std::ostream &str, const std::vector<u_char> &obj);

/// Overloaded output stream operator for a vector of byte vectors.
/// \param str - Output stream reference.
/// \param obj - Vector of byte vectors object reference.
/// \return - modified output stream.
std::ostream &operator <<(std::ostream &str, const std::vector<std::vector<u_char>> &obj);
