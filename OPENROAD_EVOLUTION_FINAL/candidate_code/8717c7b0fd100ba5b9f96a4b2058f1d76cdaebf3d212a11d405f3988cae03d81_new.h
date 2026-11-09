// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29937635;
  double density_weight = 0.43724903;
  double prefix_weight = 0.36070489;
  double neighborhood_weight = 0.14011340;
  double late_weight = 0.12038247;
  double critical_weight = 0.35389422;
  unsigned budget = 36;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
