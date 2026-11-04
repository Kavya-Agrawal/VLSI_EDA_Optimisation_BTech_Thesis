// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98342192;
  double density_weight = 0.56642650;
  double prefix_weight = 0.24211863;
  double neighborhood_weight = 0.15751791;
  double late_weight = 0.24792656;
  double critical_weight = 0.12207256;
  unsigned budget = 4;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
