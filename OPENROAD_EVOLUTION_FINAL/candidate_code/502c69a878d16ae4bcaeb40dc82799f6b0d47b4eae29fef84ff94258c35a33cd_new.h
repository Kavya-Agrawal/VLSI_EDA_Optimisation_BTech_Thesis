// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55976685;
  double density_weight = 0.08344751;
  double prefix_weight = 0.23808363;
  double neighborhood_weight = 0.25206813;
  double late_weight = 0.29570689;
  double critical_weight = 0.10408900;
  unsigned budget = 7;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
